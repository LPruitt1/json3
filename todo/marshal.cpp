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
* Tasks correspond to an Object. Each field in the Task is represented by a string (key),
*                                and each of those fields' values are represented by a Var (value).
* 
* TodoLists correspond to an Object. Each field in the TodoList is represented by a string (key),
*                                    and each of those fields' values are represented by a Var (value);
*                                    The final Var (value) represents an Array of Objects, meaning the
*                                    layering is Object > Array > Object.
*/


json::Object marshalTask(Task const& task) {
    std::map<string, json::Var> map;
    
    // Inserts more "primitive" fields
    map.insert({ "id", task.id });
    map.insert({ "title", task.title });
    map.insert({ "done", task.done });

    // Pushes values from vector<string> into vector<Var> before adding them to the map
    std::vector<json::Var> array;
    for (string const& tag : task.tags) {
        json::Var v = tag;
        array.push_back(tag);
    }
    map.insert({ "tags", array });

    // Checks for "completed" being constructed and adds it to the map if so
    if (task.completed) {
        map.insert({ "completed", *task.completed });
    }
    else {
        map.insert({ "completed", nullptr });
    }

    json::Object obj = map;
    return obj;
}


json::Var marshal(TodoList const& list) {
    std::map<string, json::Var> map;

    // Inserts more "primitive" fields
    map.insert({ "nextId", list.nextId });

    // Pushes values from vector<Task> into vector<Var> before adding them to the map
    std::vector<json::Var> array;
    for (Task const& todo_task : list.tasks) {
        json::Var v = marshalTask(todo_task);
        array.push_back(v);
    }
    map.insert({ "tasks", array });

    json::Var vee = map;
    return vee;
}


Task unmarshalTask(json::Data const& data) {
    Task task;
    
    if (data.isObject()) {

        /*
        * Ideal parameter makeup:
        * { "id": Var->Number,
        *   "title": Var->String,
        *   "done": Var->Boolean,
        *   "tags": Var->Array [
        *       Var->String,
        *       Var->String, etc.
        *     ],
        *   "completed": Var->String }
        * 
        * OR "completed": Var->nullptr }
        */

        json::Object obj = data.getObject();

        // Type-checking and assigning "primitive" fields
        if (obj["id"] != nullptr && obj["id"]->isNumber()) {
            task.id = (obj["id"])->getNumber();
        }
        else {
            throw MarshalError("ID is wrong!");
        }

        if (obj["title"] != nullptr && obj["title"]->isString()) {
            task.title = (obj["title"])->getString();
        }
        else {
            throw MarshalError("Title is wrong!");
        }

        if (obj["done"] != nullptr && obj["done"]->isBoolean()) {
            task.done = (obj["done"])->getBoolean();
        }

        // Turning Array of Var->Strings into a vector<string> and adding it to Task
        std::vector<string> tag_vector;
        if (obj["tags"] != nullptr && obj["tags"]->isArray()) {

            for (json::Var const& string_var : (obj["tags"])->getArray()) {
                if (string_var->isString()) {
                    tag_vector.push_back(string_var->getString());
                }
                else {
                    throw MarshalError("Tags is wrong!");
                }
            }

            task.tags = tag_vector;
        }
        else {
            throw MarshalError("Tags is wrong!");
        }

        // Type-checking and assigning "std::optional" field
        if (obj["completed"] != nullptr && obj["completed"]->isString()) {
            task.completed = (obj["completed"])->getString();
        }

    }
    else {
        throw MarshalError("Parameter should be an Object!");
    }

    return task;
}


TodoList unmarshal(json::Data& data) {
    TodoList list;

    if (data.isObject()) {

        /*
        * Ideal parameter makeup:
        *     { "nextId": Var->Number,
        *       "tasks:" Var->Array of Objects [
        *           see Task structure,
        *           see Task structure,
        *           et cetera
        *         ]
        *     }
        */

        json::Object obj = data.getObject();

        // Type-checking and assigning "nextId" field
        if (obj["nextId"] != nullptr && obj["nextId"]->isNumber()) {
            list.nextId = (obj["nextId"])->getNumber();
        }
        else {
            throw MarshalError("nextID is wrong!");
        }

        // Turning Var->Array of Var->Objects into vector<Tasks> and assigning it to TodoList
        std::vector<Task> task_vector;
        if (obj["tasks"] != nullptr && obj["nextId"]->isArray()) {

            for (json::Var const& var_o : (obj["nextId"])->getArray()) {
                if (var_o->isObject()) {
                    json::Object oh = var_o->getObject();
                    Task tee = unmarshalTask(oh);
                    task_vector.push_back(tee);
                }
                else {
                    throw MarshalError("Tasks is wrong!");
                }
            }

            list.tasks = task_vector;
        }
        else {
            throw MarshalError("Tasks is wrong!");
        }

    }
    else {
        throw MarshalError("Parameter should be an Object!");
    }

    return list;
}