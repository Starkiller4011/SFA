#ifndef COLLECTIONS_H
#define COLLECTIONS_H

template<typename T>
class List;

template<typename T>
class Node {

public:
  Node(T, Node<T>*, Node<T>*);
  inline T Data() const { return data; }
  inline Node* Next() const { return next; }
  inline Node* Previous() const { return prev; }

public:
  friend List<T>;

private:
  T data;
  Node* next;
  Node* prev;

};

template<typename T>
Node<T>::Node(T _data, Node<T>* _next, Node<T>* _prev) {
  data = _data;
  next = _next;
  prev = _prev;
}

template<typename T>
class List {

public:
  List();
  ~List();
  List(List const&);
  void Purge();
  void Append(T);
  void Prepend(T);
  T RemoveFirst();
  T RemoveLast();
  inline int Size() const { return size; }
  inline Node<T>* Head() const { return head; }
  inline Node<T>* Tail() const { return tail; }
  inline T GetFirst() const { return head->data; }
  inline T GetLast() const {return tail->data; }

private:
  Node<T>* head;
  Node<T>* tail;
  int size;

};

template<typename T>
List<T>::List() {
  head = tail = nullptr;
  size = 0;
}

template<typename T>
List<T>::~List() {
  Purge();
}

template<typename T>
List<T>::List(List const& toCopy) {
  Node<T>* copyNode = toCopy->Head();
  while(copyNode != nullptr) {
    Append(copyNode->data);
    copyNode = copyNode->next;
  }
}

template<typename T>
void List<T>::Purge() {
  Node<T>* tmp = head;
  while(tmp != nullptr) {
    tmp = head->next;
    delete head;
    head = tmp;
  }
  size = 0;
}

template<typename T>
void List<T>::Append(T elem) {
  Node<T>* newNode = new Node<T>(elem, nullptr, tail);
  if(size < 1) {
    head = tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  size++;
}

template<typename T>
void List<T>::Prepend(T elem) {
  Node<T>* newNode = new Node<T>(elem, head, nullptr);
  if(size < 1) {
    tail = head = newNode;
  } else {
    head->prev = newNode;
    head = newNode;
  }
  size++;
}

template<typename T>
T List<T>::RemoveFirst() {
  T elem;
  if(size == 1) {
    elem = head->data;
    head = tail = nullptr;
    size--;
  } else if(size < 1) {
    std::cout << "ERROR: Trying to access empty list" << std::endl;
    exit(1);
  } else {
    Node<T>* tmp = head;
    elem = tmp->data;
    head = tmp->next;
    head->prev = nullptr;
    delete tmp;
    size--;
  }
  return elem;
}

template<typename T>
T List<T>::RemoveLast() {
  T elem;
  if(size == 1) {
    elem = head->data;
    head = tail = nullptr;
    size--;
  } else if(size < 1) {
    std::cout << "ERROR: Trying to access empty list" << std::endl;
    exit(1);
  } else {
    Node<T>* tmp = tail;
    elem = tmp->data;
    tail = tmp->prev;
    tail->next = nullptr;
    delete tmp;
    size--;
  }
  return elem;
}

#endif
