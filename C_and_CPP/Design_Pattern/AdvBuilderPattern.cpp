#include<iostream>
#include<string>
#include<memory>

using namespace std;

// Product
class Pizza
{
  public:
    void setDough(const string& dough)
    {
      m_dough = dough;
    }

    void setSauce(const string& sauce)
    {
      m_sauce = sauce;
    }

    void setTopping(const string& sauce)
    {
      m_sauce = sauce;
    }

    void open() const
    {
      cout << "Pizza Details:\n"
           << "Dough: " << m_dough
           << "Sauce: " << m_sauce
           << "Topping: " << m_topping;
    }

  private:
    string m_dough;
    string m_sauce;
    string m_topping;
};

// Abstract builder
class PizzaBuilder
{
public:
  virtual ~PizzaBuilder() {};

  Pizza* getPizza()
  {
    return m_pizza.get();
  }
  void createNewPizzaProduct()
  {
    m_pizza = make_unique<Pizza>();
  }
  virtual void buildDough() = 0;
  virtual void buildSauce() = 0;
  virtual void buildTopping() = 0;

protected:
  unique_ptr<Pizza> m_pizza;
};


// Pizza Type 1
class HawaiianPizzaBuilder : public PizzaBuilder
{
  public:
    virtual ~HawaiianPizzaBuilder() {};

    virtual void buildDough()
    {
      m_pizza->setDough("cross");
    }
    virtual void buildSauce()
    {
      m_pizza->setSauce("mild");
    }
    virtual void buildTopping()
    {
      m_pizza->setTopping("ham+pineapple");
    }
};

// Pizza Type 2
class SpicyPizzaBuilder : public PizzaBuilder
{
  public:
    virtual ~SpicyPizzaBuilder() {};

    virtual void buildDough()
    {
      m_pizza->setDough("pan baked");
    }
    virtual void buildSauce()
    {
      m_pizza->setSauce("hot");
    }
    virtual void buildTopping()
    {
      m_pizza->setTopping("pepperoni+salami");
    }
};

// Creator
class Cook
{
  public:
    void openPizza()
    {
      m_pizzaBuilder->getPizza()->open();
    }
    void makePizza(PizzaBuilder* pb)
    {
      m_pizzaBuilder = pb;
      m_pizzaBuilder->createNewPizzaProduct();
      m_pizzaBuilder->buildDough();
      m_pizzaBuilder->buildSauce();
      m_pizzaBuilder->buildTopping();
    }
  private:
    PizzaBuilder* m_pizzaBuilder;
};

// Driver
int main()
{
  Cook cook;
  HawaiianPizzaBuilder hawaiianPizzaBuilder;
  SpicyPizzaBuilder    spicyPizzaBuilder;

  cook.makePizza(&hawaiianPizzaBuilder);
  cook.openPizza();

  cook.makePizza(&spicyPizzaBuilder);
  cook.openPizza();
}


