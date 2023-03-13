/*#include "product.hpp"

map <string,string> product_names
{
    {"Coffee","Καφές"},
    {"Chocolate","Σοκολάτα"},
    {"Milk","Γάλα"}
};

Product::Product(string atitle,double aprice,int aquantity):title(atitle),price(aprice),quantity(aquantity) {}

void Product::reduce_quantity()
{
    this->quantity--;
}

void Product::set_quantity(int new_quantity)
{
    this->quantity=new_quantity;
}

string Product::get_title()const
{
    return this->title;
}

string Product::description()const
{
    stringstream ss;
    ss<<"ΠΡΟΙΟΝ:"<<product_names[this->title]<<endl;
    ss<<"ΠΟΟΣΟ:"<<this->price<<endl;
    return ss.str();
}

string Product::getname()const
{
    return product_names[this->title];
}

double Product::get_price()const
{
    return this->price;
}

int Product::get_quantity()const
{
    return this->quantity;
}

ostream &operator<<(ostream &os,const Product &p)
{
    os<<"ΠΡΟΙΟΝ:"<<p.getname()<<endl;
    os<<"ΠΟΣΟ:"<<p.price<<endl;
    os<<"ΠΟΣΟΤΗΤΑ:"<<p.quantity<<endl;
    return os;
} */