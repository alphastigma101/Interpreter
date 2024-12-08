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
    template<typename Derived>
    class linkedList {
        inline static Node* head = nullptr;
        public:
            explicit linkedList() = default;
            ~linkedList() noexcept = default;
            template<typename T, typename Z, typename Y>
            inline void insert(T& key, Z& value, Y& type = nullptr) {
                if (searchValue(key))  return; /*throw runtimeerror<linkedList<Derived>>();*/
                Node* newNode = new Lists::Node(); 
                T(newNode->key) = key;
                T(newNode->value) = value;
                if (type != nullptr) Y(newNode->id) = type;      
                newNode->next = head;      
                head = newNode;    
            };
            template<typename T>
            inline static auto searchValue(T& key) {
                Node* temp = head;
                while (temp->next) {
                    if (temp->key == key) return temp->value;
                    else temp = temp->next;
                }
                // Throw an exception
            };
            template<typename T>
            inline static auto searchId(T& key) {
                Node* temp = head;
                while (temp->next) {
                    if (temp->key == key) return temp->id;
                    else temp = temp->next;
                }
                // Throw an exception
            };
            template<typename T, typename Z, typename Y>
            inline static void assign(T& key, Z& value, Y& type = nullptr) {
                Node* temp = head;
                while (temp->next) {
                    if (temp->key) {
                        temp->value = value;
                        if (type != nullptr) temp->id = type;
                    }
                    else temp = temp->next;
                }
                return;
            };
    };
   
};
#endif