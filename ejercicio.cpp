#include <vector>
#include <string>
#include <map>
#include "json11/json11.hpp"

enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };

struct Entorno;

class Variant {
public:
    typedef Variant (*proc_type)(const std::vector<Variant>&);
    typedef std::vector<Variant>::const_iterator iter;
    typedef std::map<std::string, Variant> map;

    variant_type type;
    std::string val;
    std::vector<Variant> list;
    proc_type proc;
    Entorno* env;

    Variant(variant_type type = Symbol) : type(type), env(0), proc(0) {}
    Variant(variant_type type, const std::string& val) : type(type), val(val), env(0), proc(0) {}
    Variant(proc_type proc) : type(Proc), proc(proc), env(0) {}

    std::string to_string() const;
    std::string to_json_string() const;
    static Variant from_json_string(const std::string& sjson);
    static Variant parse_json(const json11::Json& job);
};

std::string Variant::to_string() const {
    switch (type) {
        case Symbol:
        case Cadena:
            return val;
        case Number:
            return std::to_string(std::stod(val));
        case List: {
            std::string result = "(";
            for (const auto& elem : list) {
                result += elem.to_string() + " ";
            }
            if (!list.empty()) {
                result.pop_back(); // Eliminar el espacio adicional al final
            }
            result += ")";
            return result;
        }
        case Proc:
            return "<procedure>";
        default:
            return "Unknown type";
    }
}

std::string Variant::to_json_string() const {
    switch (type) {
        case Symbol:
        case Cadena:
            return "\"" + val + "\"";
        case Number:
            return std::to_string(std::stod(val));
        case List: {
            std::string result = "[";
            for (const auto& elem : list) {
                result += elem.to_json_string() + ",";
            }
            if (!list.empty()) {
                result.pop_back(); // Eliminar la coma adicional al final
            }
            result += "]";
            return result;
        }
        case Proc:
            return "\"<procedure>\"";
        default:
            return "\"Unknown type\"";
    }
}

Variant Variant::from_json_string(const std::string& sjson) {
    // Implementa la lógica para convertir la cadena JSON a un objeto Variant
    // Utiliza la biblioteca json11
    return json11::Json::parse(sjson);
}

Variant Variant::parse_json(const json11::Json& job) {
    // Implementa la lógica para convertir un objeto Json a un objeto Variant
    // Utiliza la biblioteca json11
    return Variant();  // Reemplaza esto con tu implementación real
}
