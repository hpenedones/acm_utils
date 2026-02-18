

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Shape {
 public:
  const string type;

  Shape(string type_) : type(type_){};

  virtual ~Shape() {}
};

class Triangle : public Shape {
 private:
 public:
  Triangle() : Shape("Triangle"){};

  static Shape* createObject(string args) {
    if (args != "Triangle") return NULL;
    return new Triangle();
  }
};

class Circle : public Shape {
 private:
 public:
  Circle() : Shape("Circle"){};

  static Shape* createObject(string args) {
    if (args != "Circle") return NULL;
    return new Circle();
  }
};

typedef Shape* (*ShapeCreator_Ptr)(string);

class ShapeFactory {
 public:
  static vector<ShapeCreator_Ptr> sub_type_creators;

  static void registerType(ShapeCreator_Ptr sub_type_creator) {
    sub_type_creators.push_back(sub_type_creator);
  }

  static Shape* createObject(string type) {
    for (int i = 0; i < ShapeFactory::sub_type_creators.size(); i++) {
      Shape* shape = ShapeFactory::sub_type_creators[i](type);

      if (shape != NULL) return shape;
    }
    return NULL;
  }
};

vector<ShapeCreator_Ptr> ShapeFactory::sub_type_creators;

int main(int argc, char** argv) {
  // vector<Shape *> shape_vec;

  // shape_vec.push_back(new Triangle());
  // shape_vec.push_back(new Circle());

  ShapeFactory::registerType(Triangle::createObject);
  ShapeFactory::registerType(Circle::createObject);

  Shape* shape1 = ShapeFactory::createObject("Triangle");
  Shape* shape2 = ShapeFactory::createObject("Circle");

  // cout << shape1->type << " " << shape2->type << endl;

  delete shape1;
  delete shape2;

  return 0;
}
