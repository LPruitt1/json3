#include "marshal.hpp"
#include "parse.hpp"
#include "json.hpp"

#include <sstream>
#include <string>
#include <typeinfo>


// Helper: throw a MarshallError exception
void invalid(std::string const& message, json::Data const& where) {
    std::ostringstream out;
    out << message << " in " << where;
    throw MarshalError(out.str());
}

/*
string valueType(json::Var const& var) {
    if (typeid(*var) == typeid(json::Array)) {
        return "Array";
    }
    else if (typeid(*var) == typeid(json::Boolean)) {
        return "Boolean";
    }
    else if (typeid(*var) == typeid(json::Null)) {
        return "Null";
    }
    else if (typeid(*var) == typeid(json::Number)) {
        return "Number";
    }
    else if (typeid(*var) == typeid(json::Object)) {
        return "Object";
    }
    else if (typeid(*var) == typeid(json::String)) {
        return "String";
    }
}
*/

json::Object marshalTask(Task const& task) {
    json::Array task_tags;
    for (string const& tag : task.tags) {
        (task_tags.getArray()).push_back(tag);
    }

    json::Object obj = {
        {"id", task.id},
        {"title", task.title},
        {"done", task.done},
        {"tags", task_tags}
    };

    if (task.completed) {
        (obj.getObject())["completed"] = *(task.completed);
    }

    return obj;
}

json::Var marshal(TodoList const& list) {
    json::Array task_array;
    for (Task const& task : list.tasks) {
        json::Object o = marshalTask(task);
        (task_array.getArray()).push_back(o);
    }

    json::Object obj = {
        {"nextId", list.nextId},
        {"tasks", task_array}
    };

    return json::Var(obj);
}

/*
template<typename T>
void taskFieldSet(T& task_field, json::Object const& object, string const& key) {
    json::Var field_var = task_field;
    json::Var object_value = (object.getObject()).at(key);

    if (typeid(*field_var) == typeid(*object_value)) {

        if (typeid(*field_var) == typeid(json::Boolean)) {
            task_field = object_value->getBoolean();
        }
        else if (typeid(*field_var) == typeid(json::Number)) {
            task_field = object_value->getNumber();
        }
        else if (typeid(*field_var) == typeid(json::Null)) {
            task_field = nullptr;
        }
        else if (typeid(*field_var) == typeid(json::String)) {
            task_field = object_value->getString();
        }
        else if (typeid(*field_var) == typeid(json::Array)) {
            task_field = ((json::Array&)*object_value).getArray();
        }
        else if (typeid(*field_var) == typeid(json::Object)) {
            task_field = ((json::Object&)*object_value).getObject();
        }

    }
    else {
        throw json::TypeError("Wrong data type!");
    }
}
*/

Task unmarshalTask(json::Object const& object) {
    Task task;

    for (auto pair : (object.getObject())) {
        if (pair.first != "completed" && pair.second->isNull()) {
            throw MarshalError("Missing required field!");
        }
    }

    json::Var const& obj_id = (object.getObject()).at("id");
    if (obj_id->isNumber()) {
        task.id = obj_id->getNumber();
    }
    else {
        throw json::TypeError("ID is not a Number!");
    }

    json::Var const& obj_title = (object.getObject()).at("title");
    if (obj_title->isString()) {
        task.title = obj_title->getString();
    }
    else {
        throw json::TypeError("Title is not a String!");
    }

    json::Var const& obj_done = (object.getObject()).at("done");
    if (obj_done->isBoolean()) {
        task.done = obj_done->getBoolean();
    }
    else {
        throw json::TypeError("Done is not a Boolean!");
    }

    json::Var const& obj_tags = (object.getObject()).at("tags");
    if (obj_tags->isArray()) {

        std::vector<json::Var> const& tags_array = ((json::Array&)obj_tags).getArray();
        for (json::Var const& string_var : tags_array) {

            if (string_var->isString()) {
                task.tags.push_back(string_var->getString());
            }
            else {
                throw json::TypeError("Tags is not an Array of Strings!");
            }

        }
    }
    else {
        throw json::TypeError("Tags is not an Array!");
    }

    json::Object object_copy = object;
    if ((object_copy.getObject())["completed"] != nullptr) {
        json::Var const& obj_completed = (object.getObject()).at("completed");
        if (obj_completed->isString()) {
            task.completed = obj_done->getString();
        }
        else {
            throw json::TypeError("Completed is not a String!");
        }
    }

    return task;
}

TodoList unmarshal(json::Data& data) {
    TodoList todo;

    if (data.isObject()) {

        json::Object obj = (json::Object&)data;
        
        if (obj.getObject()["nextId"]->isNumber()) {
            todo.nextId = (obj.getObject()["nextId"]->getNumber());
        }
        else {
            throw json::TypeError("NextID is not a Number!");
        }

        json::Array task_array;
        if (obj.getObject()["tasks"]->isArray()) {
            task_array = (json::Array&)obj.getObject()["tasks"];

            for (json::Var const& task_var : task_array.getArray()) {
                if (task_var->isObject()) {
                    json::Object o = (json::Object&)(*task_var);
                    Task task = unmarshalTask(o.getObject());
                    todo.tasks.push_back(task);
                }
           }
        }

    }

    return todo;
}