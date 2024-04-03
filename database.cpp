#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// 각 데이터를 저장할 노드 정의
struct Node {
    char key[100];
    char value[100];
    Node* next;

    Node(const char* key, const char* value) : next(nullptr) {
        std::strcpy(this->key, key);
        std::strcpy(this->value, value);
    }
};

class Database {
private:
    Node* head;

public:
    Database() : head(nullptr) {}

    // 데이터 삽입 (정수 타입)
    void add(const char* key, int value) {
        char strValue[100];
        std::sprintf(strValue, "%d", value);
        add(key, strValue);
    }

    // 데이터 삽입 (실수 타입)
    void add(const char* key, double value) {
        char strValue[100];
        std::sprintf(strValue, "%f", value);
        add(key, strValue);
    }

    // 데이터 삽입 (문자열 타입)
    void add(const char* key, const char* value) {
        Node* newNode = new Node(key, value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // 데이터 삽입 (배열 타입)
    void add(const char* key) {
        std::cout << "Size: ";
        int size;
        std::cin >> size;
        char arrayValue[100] = "["; // 배열 데이터를 문자열로 저장
        for (int i = 0; i < size; ++i) {
            std::cout << key << "[" << i << "]: ";
            std::cin >> arrayValue[strlen(arrayValue)]; // 문자열에 데이터 추가
            if (i < size - 1) {
                std::strcat(arrayValue, ", "); // 마지막 요소가 아니면 쉼표 추가
            }
        }
        std::strcat(arrayValue, "]"); // 배열의 마지막에 닫는 대괄호 추가
        add(key, arrayValue); // 배열 데이터 삽입
    }

    // del
    void del(const char* key) {
        if (!head) {
            std::cout << "Database is empty!" << std::endl;
            return;
        }

        Node* curr = head;
        Node* prev = nullptr;
        while (curr) {
            if (std::strcmp(curr->key, key) == 0) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        std::cout << "Not found!" << std::endl;
    }

    // list
    void list() {
        if (!head) {
            std::cout << "Database is empty!" << std::endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            std::cout << temp->key << ": " << temp->value << std::endl;
            temp = temp->next;
        }
    }

    // get
    void get(const char* key) {
        Node* temp = head;
        while (temp) {
            if (std::strcmp(temp->key, key) == 0) {
                std::cout << temp->key << ": " << temp->value << std::endl;
                return;
            }
            temp = temp->next;
        }
        std::cout << "Not found!" << std::endl;
    }

    // 해제
    ~Database() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Database db;
    char choice[100];
    
    do {
        std::cout << "Command (list, add, get, del, exit): ";
        std::cin >> choice;

        char key[100];
            if (strcmp(choice, "add") == 0){
                std::cout << "Key: ";
                std::cin >> key;
                std::cout << "Type (int, double, string, array): ";
                char dataTypeChoice[100];
                std::cin >> dataTypeChoice;

                    if (strcmp(dataTypeChoice, "int") == 0){
                        int intValue;
                        std::cout << "Value: ";
                        std::cin >> intValue;
                        db.add(key, intValue);
                        continue;
                    } else if (strcmp(dataTypeChoice, "double") == 0) {
                        double doubleValue;
                        std::cout << "Value: ";
                        std::cin >> doubleValue;
                        db.add(key, doubleValue);
                        continue;
                    } else if (strcmp(dataTypeChoice, "string") == 0) {
                        char stringValue[100];
                        std::cout << "Value: ";
                        std::cin >> stringValue;
                        db.add(key, stringValue);
                        continue;
                    } else if (strcmp(dataTypeChoice, "array") == 0) {
                        db.add(key);
                        continue;
                    } else {
                        std::cout << "Invalid Type" << std::endl;
                        continue;
                }
                continue;
            } else if (strcmp(choice, "list") == 0) {
                db.list();
                continue;
            } else if (strcmp(choice, "del") == 0) {
                std::cout << "Key: ";
                std::cin >> key;
                db.del(key);
                continue;
            } else if (strcmp(choice, "get") == 0) {
                std::cout << "Key: ";
                std::cin >> key;
                db.get(key);
                continue;
        } else if (strcmp(choice, "exit") == 0) {
                break;
        } else {
                std::cout << "Invalid Command" << std::endl;
        }
    } while (strcmp(choice, "exit") != 0);

    return 0;
}
