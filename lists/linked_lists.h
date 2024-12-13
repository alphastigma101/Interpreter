#ifndef _LINKEDLISTS_H_
#define _LINKEDLISTS_H_
#include <run_time_error.h>
namespace Lists {
    struct Node {
        void* id;
        void* value;  
        void* key;
        Node* next; 
    };
    class linkedList {
        inline static Node* head = nullptr;
        public:
            explicit linkedList() noexcept = default;
            ~linkedList() noexcept = default;
            template<typename T, typename Z, typename Y>
            inline static void insert(T& key, Z& value, Y type = nullptr) {
                if (search(key) == true) return;
                Node* newNode = new Lists::Node(); 
                newNode->key =  new T(key);
                newNode->value = new Z(value);
                if (type != nullptr) newNode->id = new Y(type);      
                newNode->next = head;      
                head = newNode;    
            };
            template<typename T>
            inline static auto get(T& key) {
                Node* temp = head;
                if (temp != nullptr) {
                    while (temp->next) {
                    if (temp->key != nullptr && *static_cast<T*>(temp->key) == key) return static_cast<T*>(temp->value);
                    else temp = temp->next;
                    }
                }
                throw;
            };
            template<typename T>
            inline static bool search(T& key) {
                Node* temp = head;
                if (temp != nullptr) {
                    while (temp->next) {
                        if (temp->key != nullptr && *static_cast<T*>(temp->key) == key) return true;
                        else temp = temp->next;
                    }
                }
                return false;
            };
            template<typename T>
            inline static Node* find(T key) {
                Node* temp = head;
                while (temp->next) {
                    if (temp->key != nullptr && *static_cast<T*>(temp->key) == key) return temp;
                    else temp = temp->next;
                }
                return nullptr;
            };
            template<typename T, typename Z, typename Y>
            inline static bool assign(T key, Z& value, Y type = nullptr) {
                Node* temp = head;
                while (temp->next) {
                    if (temp->key != nullptr && *static_cast<T*>(temp->key) == key) {
                        temp->value = new Z(value);
                        if (type != nullptr) temp->id =  new T(type);
                        return true;
                    }
                    else temp = temp->next;
                }
                return false;
            };
            template<typename T>
            inline static void display() {
                if (!head) {
                    std::cout << "List is empty." << std::endl;
                    return;
                }
                Node* temp = head;
                while (temp) {
                    // Safely convert and dereference the key
                    if (temp->key != nullptr) {
                        T* typedKey = static_cast<T*>(temp->key);
                        if (typedKey) {
                            std::cout << *typedKey << " -> ";
                        }
                    }
                    temp = temp->next;
                }
                std::cout << "NULL" << std::endl;
            };
    };
   
};
#endif