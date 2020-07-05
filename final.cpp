/**********************************************AUTHOR:HASTI DOSHI***************************************/
/*Remove the comment in main from int n and I would like to suggest interactive console for this*/

/*

    As instructed by sir I have used testcase but if you want then you can run it in interactive console also.

    The method I have followed is:--

    i) Firstly I have used hashing with chaining in order to store all the inventory and customer list.
    ii)For doing hashing with chaining the code is written below and it is well commented such that you can understand.
    iii)Then I have inventory in which there are all the function and its friend class is manager so that It can access
        all the private members.
    iv)Then I have customer list also which has different functions
    v) I have a class item_1_list which is linked list with type node that has been defined using struct for keeping track of items purchased
    vi)Then there is billing class which has 2 functions for buy_item
        -->One for testcase
        -->Second for user input
        -->there is make bill and delete item
        -->other functions are also there please go through code....


*/





#include <iostream>
#include<string>


using namespace std;

#define  l long long int

//As we need to use it again n again

static l new_id = 9400000101; // this is for case incase new customes comes while running user input one in testcases given there ws no such case


class manager; // I have just declared it defination will be at last

//type of the base item in inventory beacuse in hash table we will be having linked list at every possible spot 
//so this will be type of node

class item

{
private:


    l item_id;
    string name;
    int rate;
    int quantity;
    item* next = NULL;


public:
    //default constructor
    item()
    {
        this->item_id = 0;
        this->name = '0';
        this->rate = 0;
        this->quantity = 0;
    }
    item(l id, string name, int rate, int quantity)
    {
        this->item_id = id;
        this->name = name;
        this->rate = rate;
        this->quantity = quantity;
    }
    l getid()
    {
        return this->item_id;
    }
    string getname()
    {
        return this->name;
    }
    int getrate()
    {
        return this->rate;
    }
    int getquantity()
    {
        return this->quantity;
    }
    item* getnext()
    {
        return this->next;
    }
    void setquantity(int quantity)
    {
        this->quantity = quantity;
    }
private:

    /*I have made all the set functions private so that any alien object wont be able to change inventory*/

    void setid(l id)
    {
        this->item_id = id;
    }
    void setname(string name)
    {
        //cout << "XXXXXXXX"<<endl;
        this->name = name;
    }
    void setrate(int rate)
    {
        this->rate = rate;
    }

    void setnext(item* next)
    {
        this->next = next;
    }

    friend class item_list_base;

};


/*this is linked list at every spot*/

class item_list_base :public item
{
private:

    item* head = NULL;

public:
    /*insertion using hashing with chaining*/
    void insert_i(l i, string name, int rate, int quantity)
    {
        item* temp = new item;
        item* temp_a = new item;
        item* temp_1 = head;//temp_1 is used for traversing
        temp->setid(i);
        temp->setname(name);
        temp->setrate(rate);
        temp->setquantity(quantity);
        if (temp_1 == NULL)
        {
            head = temp;
        }
        else
        {
            if (temp_1->getid() > i)//condition for sorted list
            {
                temp->setnext(temp_1);
                head = temp;
            }
            else
            {
                while ((temp_1->getid() < temp->getid()) && (temp_1->getnext() != NULL)) //here we are in find of node next to which our new node is to be attached while chaining
                {
                    temp_a = temp_1;//we need this in case we want to add node immediately after this and our temp_1 has been updated
                    temp_1 = temp_1->getnext();

                }
                if ((temp_1->getnext() == NULL) && (temp_1->getid() < temp->getid()))
                {
                    temp_1->setnext(temp);//set the last node as temp that is new node 
                   // tail = temp;//update the tail pointer
                }
                else
                    //if not then in our temp_a while performing the while loop we have found that next id is greater so we need to insert our id right there
                {
                    temp_a->setnext(temp);
                    temp->setnext(temp_1);
                }
            }
        }

    }



    //The next function get_info_inventory is used as supporting function that is it will return pointer of type item in the hashtable(It has been called by specific bucket that is specific linked list so head ptr is already there) so we can see whatevar we want from that node using get methods


    item* get_info_inventory(l id)
    {

        item* temp = head;

        while (temp->getid() != id && temp->getnext() != NULL) //traverse till you dont find the node 
            temp = temp->getnext();
        if (temp->getnext() == NULL && temp->getid() != id) //if not found till end
        {
            cout << "not found" << endl;
            return NULL;
        }

        return temp;

    }

    /* Next we have a function delete item accessible by manager*/
    //I have followed the same method we follow in linked lists

    void delete_item(l id)  //from inventory
    {

        item* temp = head;
        item* left = new item;
        if (temp != NULL && temp->getid() == id) //traverse till not found
        {
            head = temp->getnext();
            free(temp);
            return;
        }
        while (temp != NULL && temp->getid() != id) //traverse till id not found
        {
            left = temp;
            temp = temp->getnext();
        }
        if (temp == NULL)
        {
            cout << "id not found how to delete!!!!!"; //if not found
            return;
        }
        left->setnext(temp->getnext());


    }

    //public function
    //In order to display whole inventory

    void display() {
        item* temp = head;
        while (temp != NULL)
        {

            cout << temp->getid() << " ";
            cout << temp->getname() << " ";
            cout << temp->getrate() << " ";
            cout << temp->getquantity() << "-->";
            temp = temp->getnext();
        }

    }

    //this is a function accesible by manager.
    void update_item(l i, string name, int rate, int quantity)
    {
        item* temp = head;
        while (temp->getid() != i && temp->getnext() != NULL)
            temp = temp->getnext();
        temp->setid(i);
        temp->setname(name);
        temp->setrate(rate);
        temp->setquantity(quantity);
    }
    friend class inventory; // not necessarily required as we are already inheriting it but for safety purpose we do it

};

class inventory :public item_list_base
{


    item_list_base* a = new item_list_base[100];  // pointer to 100 linked lists of each bucket


private:


    //whichever function we put private are only accessible by manager::-

    void update_item(l i, string name, int rate, int quantity)
    {
        a[i % 100].update_item(i, name, rate, quantity);
    }

    //insertion in inventory is also private

    void insert_i(l i, string name, int rate, int quantity)
    {
        a[i % 100].insert_i(i, name, rate, quantity);
    }

    //delete item is private

    void delete_item(l id)
    {
        a[id % 100].delete_item(id);
    }

    //these are made for convinience as we hv get info function no need of these but then too I have made them

    int search_rate(l id)
    {
        int item_hash = id % 100;
        item* h = a[item_hash].get_info_inventory(id);
        return h->getrate();
    }
    string search_name(l item_ID)
    {
        item* h = a[item_ID % 100].get_info_inventory(item_ID);
        return h->getname();
    }


public:


    item* get_info_inventory(l i)
    {
        item* temp_r = a[i % 100].get_info_inventory(i);
        return temp_r;
    }

    /*when one purchases one needs to update stock*/

    void update_stock(l id, int sold)
    {
        item* temp_r = a[id % 100].get_info_inventory(id);
        temp_r->setquantity(temp_r->getquantity() - sold);
    }


    //we have a case where if users tells the bill function before billing that I dont want this item then delete it from bill now when I have inserted a item in bill I have updated the stock so when someone insisted to delte item then again I need to update the stocks


    void update_stock_while_deletion(l id, int q)
    {
        item* temp_r = a[id % 100].get_info_inventory(id);
        temp_r->setquantity(temp_r->getquantity() + q);
    }


    void display()
    {
        int i;
        for (i = 0; i < 100; i++)
        {
            a[i].display();
            cout << endl;
        }
    }

    friend class manager;
};




class customer

{
private:
    l customer_id;
    string name;
    int rewards;
    customer* next = NULL;
public:
    customer()
    {
        this->customer_id = 0;
        this->name = '0';
        this->rewards = 0;

    }
    customer(l id, string name, int rewards)
    {
        this->customer_id = id;
        this->name = name;
        this->rewards = rewards;

    }

    l getidc()
    {
        return this->customer_id;
    }
    string getnamec()
    {
        return this->name;
    }
    int getrewardsc()
    {
        return this->rewards;
    }
    customer* getnextc()
    {
        return this->next;
    }
private:
    void setidc(l id)
    {
        this->customer_id = id;
    }
    void setnamec(string name)
    {
        this->name = name;
    }

    void setnextc(customer* next)
    {
        this->next = next;
    }

public:
    void setrewardsc(int rewards)
    {
        this->rewards = rewards;
    }



    friend class customer_list_base;


};
class customer_list_base :public customer
{

public:
    customer* head = NULL;
    // node* tail=NULL;

    void insertc(l i, string name, int rewards)
    {
        customer* temp = new customer;
        customer* temp_a = new customer;
        customer* temp_1 = head;//temp_1 is used for traversing

        temp->setidc(i);
        temp->setnamec(name);
        temp->setrewardsc(rewards);

        if (temp_1 == NULL)
        {
            head = temp;
            // tail = temp;
        }
        else
        {
            if (temp_1->getidc() > i)
            {
                temp->setnextc(temp_1);
                head = temp;
            }
            else
            {
                while ((temp_1->getidc() < temp->getidc()) && (temp_1->getnextc() != NULL))
                {
                    temp_a = temp_1;
                    temp_1 = temp_1->getnextc();

                }
                if ((temp_1->getnextc() == NULL) && (temp_1->getidc() < temp->getidc()))
                {
                    temp_1->setnextc(temp);
                }
                else
                {
                    temp_a->setnextc(temp);
                    temp->setnextc(temp_1);
                }
            }
        }

    }


    customer* get_customer_info(l id)
    {
        customer* temp = head;
        while (temp->getidc() != id && temp->getnextc() != NULL)
            temp = temp->getnextc();
        if (temp->getnextc() == NULL && temp->getidc() != id)
            cout << "not found" << endl;

        return temp;

    }


    void displayc() {
        customer* temp = head;
        while (temp != NULL)
        {

            cout << temp->getidc() << " ";
            cout << temp->getnamec() << " ";
            cout << temp->getrewardsc() << " " << "-->";
            temp = temp->getnextc();
        }
    }




    void update_cust(l i, string name, int rew)
    {
        customer* temp = head;

        while (temp->getidc() != i && temp->getnextc() != NULL)
            temp = temp->getnextc();

        temp->setidc(i);
        temp->setnamec(name);
        temp->setrewardsc(rew);


    }


    void Update_points(l id, int tm)
    {
        customer* temp = head;
        while (temp->getidc() != id && temp->getnextc() != NULL)
            temp = temp->getnextc();
        temp->setrewardsc(tm);

    }



    void delete_cust(l id)
    {
        customer* temp = head;
        customer* left = new customer;
        if (temp != NULL && temp->getidc() == id)
        {
            head = temp->getnextc();
            free(temp);
            return;
        }
        while (temp != NULL && temp->getidc() != id)
        {
            left = temp;
            temp = temp->getnextc();
        }
        if (temp == NULL)
        {
            cout << "id not found how to delete!!!!!";
            return;
        }
        left->setnextc(temp->getnextc());
    }


    friend class customer_list;
    friend class manager;

};

class customer_list : public customer_list_base
{
    friend class manager;

private:

    customer_list_base* b = new customer_list_base[100];

    void displayc()
    {
        int i;
        for (i = 0; i < 100; i++)
        {
            b[i].displayc();
            cout << endl;
        }
    }

    void insertc(l i, string name, int rewards)
    {
        b[i % 100].insertc(i, name, rewards);
    }

    void update_cust(l i, string name, int rew)
    {
        b[i % 100].update_cust(i, name, rew);
    }

    void delete_cust(l id)
    {
        b[id % 100].delete_cust(id);
    }


public:

    void Add_Customer(l id, string name, int rewards)
    {
        this->insertc(id, name, rewards);
    }



    void Update_points(l id, int tm)
    {
        b[id % 100].Update_points(id, tm);
    }


    //supporting function

    customer* get_customer_info(l i)
    {
        customer* temp_x = b[i % 100].get_customer_info(i);
        return temp_x;
    }

    int get_points(l id)
    {
        customer* temp_x = b[id % 100].get_customer_info(id);
        return temp_x->getrewardsc();
    }


};
//for billing list
struct node
{
    l id;
    string name;
    int rate;
    int quantity;
    int amount;
    node* next;
};

struct node* head_item_1;
//billing linked_list
class item_1_list

{
    node* head, * tail;
public:
    item_1_list()
    {
        head = NULL;
        tail = NULL;
    }

    //simple linked list

    void add_node(l id, string name, int rate, int quantity, int amount)
    {
        node* tmp = new node;
        tmp->id = id;
        tmp->name = name;
        tmp->rate = rate;
        tmp->quantity = quantity;
        tmp->amount = amount;
        tmp->next = NULL;

        if (head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    //In order to delete

    node* gethead()
    {
        return head;
    }


    //supporting functions

    static void display_item_1(node* head)
    {
        if (head == NULL)
        {
            return;
        }
        else
        {

            cout << head->id << "    ";
            cout << head->name << "    ";
            cout << head->rate << "    ";
            cout << "\t" << head->quantity << "   \t";
            cout << "   " << head->amount << "    " << endl;
            display_item_1(head->next);
        }
    }



    void delete_node(l id)/*in case person changes mind*/
    {
        node* ttmp = head;

        if (head->id == id)
        {
            head_item_1 = head->next;
        }

        node* prev = new node;
        while (ttmp->id != id)
        {
            prev = ttmp;
            ttmp = ttmp->next;
        }

        prev->next = ttmp->next;
    }

    //getting quantity so if person wants to delete item from puchased list I can use it in stock_updation

    int getq(l pr)
    {
        node* ttmp = head;
        while (ttmp->id != pr)
        {
            ttmp = ttmp->next;
        }
        return ttmp->quantity;
    }

    int geta(l pr)
    {
        node* ttmp = head;
        while (ttmp->id != pr)
        {
            ttmp = ttmp->next;
        }
        return ttmp->amount;
    }


    //total bill amount


    int gettm(node* head)
    {
        int sum = 0;
        node* ttmp = head;
        while (ttmp)
        {
            sum = sum + ttmp->amount;
            ttmp = ttmp->next;
        }
        return sum;
    }
};


class manager
{
    l id;
    string name;

public:

    void insert_i(inventory i, l item_id, string name, int rate, int quantity)
    {
        i.insert_i(item_id, name, rate, quantity);
    }
    void insertc(customer_list c, l id, string name, int rewards)
    {
        c.insertc(id, name, rewards);
    }
    item* get_info_inventory(inventory i, l id)
    {
        item* x = i.get_info_inventory(id);
        return x;
    }
    customer* get_customer_info(l id)
    {
        customer* x = this->get_customer_info(id);
        return x;
    }
    void disp_node(l id, inventory i)
    {
        item* temp = i.get_info_inventory(id);
        cout << temp->getid() << "\t";
        cout << temp->getname() << "\t";

        cout << temp->getrate() << "\t";
        cout << temp->getquantity() << "\t";
    }
    void disp_c_node(l id, customer_list c)
    {
        customer* temp = c.get_customer_info(id);
        cout << "-----------------------------------------------------------------------------" << endl;

        cout << "Name\t\t" << "ID\t" << "Rewards\t" << endl;
        cout << temp->getidc() << "\t";
        cout << temp->getnamec() << "\t";
        cout << temp->getrewardsc() << "\t";
    }
    void display(inventory i)
    {
        i.display();
    }

    void delete_item(inventory i, l id)
    {

        i.delete_item(id);
    }
    void displayc(customer_list c)
    {
        c.displayc();
    }
    void update_item(l id, string name, int rate, int quantity, inventory i)
    {
        i.update_item(id, name, rate, quantity);
    }
    void update_cust(l id, string name, int rew, customer_list c)
    {
        c.update_cust(id, name, rew);
    }
    void delete_cust(customer_list c, l id)
    {
        c.delete_cust(id);
    }
    void update_stock(inventory i, l id, int q)
    {
        i.update_stock(id, q);
    }
    void update_points(customer_list c, int tm, l id)
    {
        c.Update_points(id, tm);
    }


};

item_1_list accesfordel;//this will have node to item purchased list because we need head node if we want to elete certain item

class billing : public inventory, public customer_list
{
    item_1_list p;
    l transaction_id;
    l customer_id;
    int ch;
    int t_amount;
public:
    billing()
    {
        transaction_id = 0;
        customer_id = 0;
        t_amount = 0;
    }
    billing(l tr_id, l c_id)
    {
        this->transaction_id = tr_id;
        this->customer_id = c_id;

    }


    //this will take the product id from main while I have another function which will take from user when Buy item is //called

    void Buy_item_testcase(inventory a, customer_list c, l product_id, int q)
    {
        item* temp_o = a.get_info_inventory(product_id);
        if (temp_o != NULL)
        {
            string nama = temp_o->getname();
            int ratea = temp_o->getrate();

            p.add_node(product_id, nama, ratea, q, ratea * q);

            a.update_stock(product_id, q);

            head_item_1 = p.gethead();

            accesfordel = p;
        }
    }


    //This function is for menu driven which will diplay all the statements n all

    l BuyItem(inventory a, customer_list c)
    {

        if (customer_id == 99)
        {
            string naim;
            cout << "Please enter your name:";
            cin >> naim;
            c.Add_Customer(new_id, naim, 0);
            cout << "Your new id is :-";
            cout << new_id;
            new_id++;

        }

        int no_of_item;
        cout << "Enter number of items you want to purchase ";
        cin >> no_of_item;

        while (no_of_item--)
        {
            cout << "Please add product id you want to purchase:-";

            l prid;
            cin >> prid;

            item* temp_o = a.get_info_inventory(prid);
            if (temp_o != NULL)
            {
                string nama = temp_o->getname();
                int ratea = temp_o->getrate();

                int q;
                cout << "Enter quantity:-";

                cin >> q;

                p.add_node(prid, nama, ratea, q, ratea * q);
                a.update_stock(prid, q);
                p.display_item_1(p.gethead());
                head_item_1 = p.gethead();
                accesfordel = p;
            }
        }
        return new_id--;
    }



    void cancelitem(inventory a)
    {

        cout << "HERE IS LIST OF ITEMS PURCHASE :-" << endl;
        p.display_item_1(head_item_1);
        cout << "please enter the product id of item you dont want now:--" << endl;
        l prif;//id input
        cin >> prif;
        int x = accesfordel.getq(prif);
        a.update_stock_while_deletion(prif, x);//if we delete the stock needs to be updated
        accesfordel.delete_node(prif);
        accesfordel.display_item_1(head_item_1);

    }



    void Make_Bill(l cid, customer_list cl, manager c)
    {
        cout << "----------------------------------------------------------" << endl;

        cout << "Transaction ID: " << ++transaction_id << "\t\t";
        cout << "Customer ID is: " << cid << endl;
        cout << "----------------------------------------------------------" << endl;

        cout << "Product ID   " << "  Name  " << "  Rate  " << "  Quantity  " << "  Amount   " << endl;

        cout << "----------------------------------------------------------" << endl;
        //cout << "Here is list of items you have bought:--" << endl;
        accesfordel.display_item_1(head_item_1);
        cout << "----------------------------------------------------------" << endl;

        int m = accesfordel.gettm(head_item_1);
        cout << "Your total amount is:--" << " " << m << endl;
        cout << "----------------------------------------------------------" << endl;


        c.update_points(cl, m, cid);

        cout << endl << endl << endl << "***************************THANKYOU FOR VISITING TO FAM_JAM  SUPERMARKET****************************" << endl << endl << endl;
    }

};


int main()
{

    inventory inv;
    customer_list c;

    manager a;
    item haship[100] = { {111100000001,"1",100,20},{111100000002,"2",110,20},{111100000003,"3",120,20},{111100000004,"4",130,20},
      {111100000005,"5",140,20},{111100000006,"6",150,20},{111100000007,"7",160,20},{111100000008,"8",170,20},{111100000009,"9",180,20},{111100000010,"10",190,20},
      {111100000011,"11",200,20},
      {111100000012,"12",210,20},{111100000013,"13",220,20},{111100000014,"14",230,20},{111100000015,"15",240,20},{111100000016,"16",250,20},
      {111100000017,"17",260,20},{111100000018,"18",270,20},{111100000019,"19",280,20},{111100000020,"20",290,20},{111100000021,"21",300,20},
      {111100000022,"22",310,20},{111100000023,"23",320,20},{111100000024,"24",330,20},{111100000025,"25",340,20},{111100000026,"26",350,20},
      {111100000027,"27",360,20},{111100000028,"28",370,20},{111100000029,"29",380,20},{111100000030,"30",390,20},{111100000031,"31",400,20},
      {111100000032,"32",410,20},{111100000033,"33",420,20},{111100000034,"34",430,20},{111100000035,"35",440,20},{111100000036,"36",450,20},
      {111100000037,"37",460,20},{111100000038,"38",470,20},{111100000039,"39",480,20},{111100000040,"40",490,20},{111100000041,"41",500,20},
      {111100000042,"42",510,20},{111100000043,"43",520,20},{111100000044,"44",530,20},{111100000045,"45",540,20},{111100000046,"46",550,20},
      {111100000047,"47",560,20},{111100000048,"48",570,20},{111100000049,"49",580,20},{222200001111,"50",590,20},{222200001114,"51",600,20},
      {222200001117,"52",610,20},{222200001120,"53",620,20},{222200001123,"54",630,20},{222200001126,"55",640,20},{222200001129,"56",650,20},
      {222200001132,"57",660,20},{222200001135,"58",670,20},{222200001138,"59",680,20},{222200001141,"60",690,20},{222200001144,"61",700,20},
      {222200001147,"62",710,20},{222200001150,"63",720,20},{222200001153,"64",730,20},{222200001156,"65",740,20},{222200001159,"66",750,20},
      {222200001162,"67",760,20},{222200001165,"68",770,20},{222200001168,"69",780,20},{222200001171,"70",790,20},{222200001174,"71",800,20},
      {222200001177,"72",810,20},{222200001180,"73",820,20},{222200001183,"74",830,20},{222200001186,"75",840,20},{222200001189,"76",850,20},
      {222200001192,"77",860,20},{222200001195,"78",870,20},{222200001198,"79",880,20},{222200001201,"80",890,20},{222200001204,"81",900,20},
      {222200001207,"82",910,20},{222200001210,"83",920,20},{222200001213,"84",930,20},{222200001216,"85",940,20},{222200001219,"86",950,20},
      {222200001222,"87",960,20},{222200001225,"88",970,20},{222200001228,"89",980,20},{222200001231,"90",990,20},{222200001234,"91",1000,20},
      {222200001237,"92",1010,20},{222200001240,"93",1020,20},{222200001243,"94",1030,20},{222200001246,"95",1040,20},{222200001249,"96",1050,20},
      {222200001252,"97",1060,20},{222200001255,"98",1070,20},{222200001258,"99",1080,20},{222200001261,"100",1090,20}, };

    customer haship_1[100] = { {9400000001,"1",0},{9400000002,"2",0},{9400000003,"3",0},{9400000004,"4",0},{9400000005,"5",0},{9400000006,"6",0},{9400000007,"7",0},{9400000008,"8",0},{9400000009,"9",0},{9400000010,"10",0},
 {9400000011,"11",0},{9400000012,"12",0},{9400000013,"13",0},{9400000014,"14",0},{9400000015,"15",0},{9400000016,"16",0},{9400000017,"17",0},{9400000018,"18",0},{9400000019,"19",0},{9400000020,"20",0},
 {9400000021,"21",0},{9400000022,"22",0},{9400000023,"23",0},{9400000024,"24",0},{9400000025,"25",0},{9400000026,"26",0},{9400000027,"27",0},{9400000028,"28",0},{9400000029,"29",0},{9400000030,"30",0},
 {9400000031,"31",0},{9400000032,"32",0},{9400000033,"33",0},{9400000034,"34",0},{9400000035,"35",0},{9400000036,"36",0},{9400000037,"37",0},{9400000038,"38",0},{9400000039,"39",0},{9400000040,"40",0},
 {9400000041,"41",0},{9400000042,"42",0},{9400000043,"43",0},{9400000044,"44",0},{9400000045,"45",0},{9400000046,"46",0},{9400000047,"47",0},{9400000048,"48",0},{9400000049,"49",0},{9400000050,"50",0},
 {9400000051,"51",0},{9400000052,"52",0},{9400000053,"53",0},{9400000054,"54",0},{9400000055,"55",0},{9400000056,"56",0},{9400000057,"57",0},{9400000058,"58",0},{9400000059,"59",0},{9400000060,"60",0},
 {9400000061,"61",0},{9400000062,"62",0},{9400000063,"63",0},{9400000064,"64",0},{9400000065,"65",0},{9400000066,"66",0},{9400000067,"67",0},{9400000068,"68",0},{9400000069,"69",0},{9400000070,"70",0},
 {9400000071,"71",0},{9400000072,"72",0},{9400000073,"73",0},{9400000074,"74",0},{9400000075,"75",0},{9400000076,"76",0},{9400000077,"77",0},{9400000078,"78",0},{9400000079,"79",0},{9400000080,"80",0},
 {9400000081,"81",0},{9400000082,"82",0},{9400000083,"83",0},{9400000084,"84",0},{9400000085,"85",0},{9400000086,"86",0},{9400000087,"87",0},{9400000088,"88",0},{9400000089,"89",0},{9400000090,"90",0},
 {9400000091,"91",0},{9400000092,"92",0},{9400000093,"93",0},{9400000094,"94",0},{9400000095,"95",0},{9400000096,"96",0},{9400000097,"97",0},{9400000098,"98",0},{9400000099,"99",0},{9400000100,"100",0},
    };

    /*manager objects are designed such that in case there are multiple managers it will be able to cope up that is if
    one manager changes the data base then other will be able to witness it!!)*/
    manager b;
    for (int i = 0; i < 100; i++)
    {
        b.insertc(c, haship_1[i].getidc(), haship_1[i].getnamec(), haship_1[i].getrewardsc());

    }

    for (int i = 0; i < 100; i++)
        a.insert_i(inv, haship[i].getid(), haship[i].getname(), haship[i].getrate(), haship[i].getquantity());
    //static l transactio_id = 1;
   // cid;
    static l transactio_id = 900;


    //here I provide some testcase then comes user input program
    
    cout << endl << endl << endl << "*****************************WELCOME TO FAM JAM SUPERMARKET*********************************" << endl << endl << endl;


    billing h(transactio_id, 9400000011);
    h.Buy_item_testcase(inv, c, 111100000011, 3);
    h.Buy_item_testcase(inv, c, 222200001114, 1);
    h.Buy_item_testcase(inv, c, 222200001234, 2);
    h.Make_Bill(9400000011, c, b);


    cout << "After billing is called:-";
    cout << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Customer info:-" << endl;

    b.disp_c_node(9400000011, c);
    cout << endl;

    cout << "-----------------------------------------------------------------------------" << endl;


    cout << "Updated Inventory" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    cout << "Product_ID\t" << "Name\t" << "Rate\t" << "Quantity\t" << endl;

    a.disp_node(111100000011, inv);
    cout << endl;
    a.disp_node(222200001114, inv);
    cout << endl;
    a.disp_node(222200001234, inv);
    cout << endl;




    cout << endl << endl << endl << "*****************************WELCOME TO FAM JAM SUPERMARKET*********************************" << endl << endl << endl;


    billing m(++transactio_id, 9400000001);


    m.Buy_item_testcase(inv, c, 111100000009, 3);
    m.Buy_item_testcase(inv, c, 111100000010, 1);
    m.Buy_item_testcase(inv, c, 111100000011, 2);

    h.Make_Bill(9400000001, c, b);




    cout << "After billing is called:-";
    cout << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "Customer info:-" << endl;

    b.disp_c_node(9400000001, c);
    cout << endl;

    cout << "-----------------------------------------------------------------------------" << endl;


    cout << "Updated Inventory" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    cout << "Product_ID\t" << "Name\t" << "Rate\t" << "Quantity\t" << endl;



    a.disp_node(111100000009, inv);//using manager
    cout << endl;
    a.disp_node(111100000010, inv);
    cout << endl;
    a.disp_node(111100000011, inv);
    cout << endl;

    
    
    
    //FROM HERE THE ACTUAL USER INPUT CODE STARTS

    l cid, mid, x_id, f_id,d_id;//used for different inputs just declared for safety

    int in;

    int check = 0;
    cout << "If you want to run menu driven program please go for it(please press 3)";
    cin >> check;

    if (check == 3)
    {
    come_here:

        cout << "please press 1 if you are manager and 2 if you are cashier/customer:--";
        cin >> in;
        if (in == 2)
        {

        go_there:
            while (1)
            {
                int ch = 0;
                cout << "Please Enter Customer ID (If new customer press 99)" << endl;
                cin >> cid;


                while (1)
                {
                    cout << endl;

                    cout << "Enter 1 to buy item" << endl;
                    cout << "Enter 2 to delete item" << endl;
                    cout << "Enter 3 to make bill" << endl;
                    cout << "Enter 0 to exit" << endl;

                    cin >> ch;
                    billing u(++transactio_id, cid);


                    switch (ch)

                    {
                    case 1:
                        u.BuyItem(inv, c);
                        break;

                    case 2:
                        u.cancelitem(inv);
                        break;

                    case 3:
                        if (cid == 99)
                        {
                            u.Make_Bill(new_id--, c, b);
                        }
                        else

                            u.Make_Bill(cid, c, b);
                        goto go_there;
                        break;
                    case 0:
                        goto come_here;

                    default:
                        break;
                    }

                }

            }

        }
        l true_id = 201901302;
        string true_name = "hasti";

        string m_name;
        if (in == 1)
        {
            int k;
            std::cout << "Please note manager credentials for this program are id =201901302 name = hasti"<<endl;
            std::cout << "please enter manager creadentials:-" << endl << "Enter your id:";
            std::cin >> mid;
            std::cout << endl << "name please";
            std::cin >> m_name;
            l k_id;
            string k_name = "0";
            int k_rate = 0;
            int k_quan = 0;
            l h_id = 0;
            string h_name = "0";
            int h_rew = 0;
            if (mid == true_id && m_name == true_name)
            {
                cout << "Enter 1 to update item" << endl << "Enter 2 to update customer" << endl << "Enter 3 to delete customer" << endl << "Enter 4 to delete item" << endl <<"Enter 5 to display item node"<<endl<<"Enter 6 to display customer"<<endl <<"Enter 7 to exit";
                cin >> k;
                switch (k)
                {
                case 1:
                    std::cout << "Enter id of item you want to update:";
                    std::cin >> k_id;
                    std::cout << "Enter product name:";
                    std::cin >> k_name;
                    std::cout << endl;
                    std::cout << "Enter rate:";
                    std::cin >> k_rate;
                    std::cout << endl;
                    std::cout << "Enter Quantity:";
                    std::cin >> k_quan;
                    a.update_item(k_id, k_name, k_rate, k_quan, inv);
                    break;

                case 2:
                    std::cout << "Enter id of customer you want to update:";
                    std::cin >> h_id;
                    std::cout << "Enter customer name:";
                    std::cin >> h_name;
                    std::cout << endl;
                    std::cout << "Enter rewards:";
                    std::cin >> h_rew;
                    std::cout << endl;
                    b.update_cust(h_id, h_name, h_rew, c);
                    break;
                case 3:
                    std::cout << "Enter customer ID you want to delete:";
                    std::cin >> x_id;
                    b.delete_cust(c, x_id);
                    break;
                case 4:
                    std::cout << "Enter product id you want to delete: ";
                    std::cin >> f_id;
                    a.delete_item(inv, f_id);
                    break;
                case 5:
                    std::cout << "Enter the product id you want to display:";
                    std::cin >> f_id;
                    cout << "Product_ID\t" << "Name\t" << "Rate\t" << "Quantity\t" << endl;
                    a.disp_node(f_id, inv);
                case 6:
                    std::cout << "Enter the customer id you want to display:";
                    std::cin >> d_id;
                    b.disp_c_node(d_id, c);
                    cout << endl;

                case 7:
                    goto go_there;
                default:
                    break;
                }
            }
        }
    }
}
