#include <iostream>
#include <vector>
#include <map>
#include <variant>
#include <sstream>
#include <iomanip>

class Variant {
public:
    // Definir tipos de datos que pueden ser almacenados en Variant
    using ValueType = std::variant<int, double, std::string, std::vector<Variant>, std::map<std::string, Variant>>;

    // Constructores
    Variant() = default;
    Variant(const ValueType& value) : value_(value) {}

    // Métodos de conversión a cadena y formato JSON
    std::string to_string() const;
    std::string to_json_string() const;

    // Métodos estáticos para convertir desde cadena JSON a Variant
    static Variant from_json_string(const std::string& json);
    static Variant parse_json(const std::string& json);

private:
    ValueType value_;

    // Funciones auxiliares
    static std::string escape_json_string(const std::string& input);
};

// Implementación de los métodos

std::string Variant::to_string() const {
    if (std::holds_alternative<int>(value_)) {
        return std::to_string(std::get<int>(value_));
    } else if (std::holds_alternative<double>(value_)) {
        return std::to_string(std::get<double>(value_));
    } else if (std::holds_alternative<std::string>(value_)) {
        return std::get<std::string>(value_);
    } else if (std::holds_alternative<std::vector<Variant>>(value_)) {
        std::string result = "[ ";
        const auto& vec = std::get<std::vector<Variant>>(value_);
        for (const auto& element : vec) {
            result += element.to_string() + " ";
        }
        result += "]";
        return result;
    } else if (std::holds_alternative<std::map<std::string, Variant>>(value_)) {
        std::string result = "{ ";
        const auto& map = std::get<std::map<std::string, Variant>>(value_);
        for (const auto& [key, val] : map) {
            result += escape_json_string(key) + ": " + val.to_string() + ", ";
        }
        if (!map.empty()) {
            // Eliminar la coma adicional al final
            result.pop_back();
            result.pop_back();
        }
        result += " }";
        return result;
    } else {
        return "Unknown type";
    }
}

std::string Variant::to_json_string() const {
    std::ostringstream oss;
    oss << std::setw(4) << to_json_string();
    return oss.str();
}

std::string Variant::escape_json_string(const std::string& input) {
    // Escapar caracteres especiales en una cadena JSON
    std::string result;
    for (char c : input) {
        switch (c) {
            case '"':
                result += "\\\"";
                break;
            case '\\':
                result += "\\\\";
                break;
            case '/':
                result += "\\/";
                break;
            case '\b':
                result += "\\b";
                break;
            case '\f':
                result += "\\f";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            default:
                result += c;
                break;
        }
    }
    return result;
}

std::string Variant::to_json_string() const {
    if (std::holds_alternative<int>(value_)) {
        return std::to_string(std::get<int>(value_));
    } else if (std::holds_alternative<double>(value_)) {
        return std::to_string(std::get<double>(value_));
    } else if (std::holds_alternative<std::string>(value_)) {
        return "\"" + escape_json_string(std::get<std::string>(value_)) + "\"";
    } else if (std::holds_alternative<std::vector<Variant>>(value_)) {
        std::string result = "[ ";
        const auto& vec = std::get<std::vector<Variant>>(value_);
        for (const auto& element : vec) {
            result += element.to_json_string() + ", ";
        }
        if (!vec.empty()) {
            // Eliminar la coma adicional al final
            result.pop_back();
            result.pop_back();
        }
        result += " ]";
        return result;
    } else if (std::holds_alternative<std::map<std::string, Variant>>(value_)) {
        std::string result = "{ ";
        const auto& map = std::get<std::map<std::string, Variant>>(value_);
        for (const auto& [key, val] : map) {
            result += "\"" + escape_json_string(key) + "\": " + val.to_json_string() + ", ";
        }
        if (!map.empty()) {
            // Eliminar la coma adicional al final
            result.pop_back();
            result.pop_back();
        }
        result += " }";
        return result;
    } else {
        return "Unknown type";
    }
}

Variant Variant::from_json_string(const std::string& json) {
    // Implementar la lógica para convertir una cadena JSON a Variant
    // Puedes usar bibliotecas como jsoncpp o implementar tu propio analizador JSON

    // Aquí, simplemente devolvemos un Variant que contiene la cadena JSON sin procesar
    return Variant(json);
}

Variant Variant::parse_json(const std::string& json) {
    // Implementar la lógica para convertir una cadena JSON a Variant
    // Puedes usar bibliotecas como jsoncpp o implementar tu propio analizador JSON

    // Aquí, simplemente devolvemos un Variant que contiene la cadena JSON sin procesar
    return Variant(json);
}

int main() {
    // Ejemplo de uso
    Variant v1 = 42;
    Variant v2 = 3.14;
    Variant v3 = "Hello, World!";
    Variant v4 = std::vector<Variant>{1, 2, 3};
    Variant v5 = std::map<std::string, Variant>{{"key1", 10}, {"key2", "value"}};

    std::cout << "v1: " << v1.to_string() << std::endl;
    std::cout << "v2: " << v2.to_string() << std::endl;
    std::cout << "v3: " << v3.to_string() << std::endl;
    std::cout << "v4: " << v4.to_string() << std::endl;
    std::cout << "v5: " << v5.to_string() << std::endl;

    std::cout << "v5 (JSON): " << v5.to_json_string() << std::endl;

    return 0;
}
