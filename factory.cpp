

#include <iostream>
#include <string>
#include <vector>

using namespace std;






class Shape {

public:
  const string type;
  
  Shape(string type_) : type(type_) {} ;

  virtual Shape* createObject(string args) = 0;

};





class Triangle : public Shape {
  
private:
  
public:

  
  Triangle() : Shape("Triangle") {};

  Triangle* createObject(string args) {
    if (strcmp(args.c_str(), type.c_str()) != 0)
      return NULL;
    return new Triangle();
  }

};



class Circle : public Shape {
  
private:
  
public:
  
  Circle() : Shape("Circle") {};

  Circle* createObject(string args) {
    if (strcmp(args.c_str(), type.c_str()) != 0)
      return NULL;
    return new Circle();
  }
};


typedef Shape* (* ShapeCreator_Ptr)(string);


class ShapeFactory {
 
  
public:
  static vector<ShapeCreator_Ptr> sub_type_creators;
  
  static void registerType(ShapeCreator_Ptr sub_type_creator) {
    sub_type_creators.push_back(sub_type_creator);
  }
 
  static Shape* createObject(string type)
  {
    for(int i=0; i<ShapeFactory::sub_type_creators.size(); i++) {
      Shape * shape = ShapeFactory::sub_type_creators[i](type);
      
      if (shape != NULL)
	return shape;
            
    }
    return NULL;
  }
  
};

vector<ShapeCreator_Ptr> ShapeFactory::sub_type_creators;


int main(int argc, char ** argv)
{

  // vector<Shape *> shape_vec;
  
  // shape_vec.push_back(new Triangle());
  // shape_vec.push_back(new Circle());
  
  ShapeFactory::registerType( (ShapeCreator_Ptr) Triangle::createObject);
  ShapeFactory::registerType( (ShapeCreator_Ptr) Circle::createObject);
 

  Shape * shape1 = ShapeFactory::createObject("Triangle");
  Shape * shape2 = ShapeFactory::createObject("Circle");

  //cout << shape1.type << " " << shape2.type << endl;

  
  return 0;
}
