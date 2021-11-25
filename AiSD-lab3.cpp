#include <iostream>

//Cyran Patryk gr B

using namespace std;

class ArrayList
{
protected:
	int* items;
	int head;
	int tail;
	int capacity;
	int size;

public:
    ArrayList(int c = 0)
    {
        head = 0;
        tail = -1;
        size = 0;
        capacity = c;
        items = new int[capacity];
    }

    bool empty()
    {
        if (getSize() == 0) return true;

        return false;
    }

    bool full()
    {
        if(getSize()==getCapacity()) return true;

        return false;
    }

    int getSize()
    {
        return size;
    }

    int getCapacity()
    {
        return capacity;
    }

    int getFirst()
    {
        if (empty())
        {
            cout << "\nLista jest pusta!";
            return -1;
        }

        return head;
    }

    int getLast()
    {
        if (empty())
        {
            cout << "\nLista jest pusta!"; 
            return -1;
        }
        return tail;
    }

    int getNext(int p)
    {
        if (empty())
        {
            cout << "\nLista jest pusta!";
            return -1;
        }

        if (p < getFirst() || p >= getLast()) 
        {
            cout << "\nTaka pozycja nie istnieje!";
            return -1;
        }

        return p + 1;
    }    
    
    int getPrev(int p)
    {
        if (empty())
        {
            cout << "\nLista jest pusta!"; 
            return -1;
        }

        if (p <= getFirst() || p > getLast())
        {
            cout << "\nTaka pozycja nie istnieje!"; 
            return -1;
        }

        return p - 1;
    }

    int retrieve(int p)
    {
        if (empty())
        {
            cout << "\nLista jest pusta!"; 
            return -1;
        }

        if (p < getFirst() || p > getLast())
        {
            cout << "\nTaka pozycja nie istnieje!";
            return -1;
        }

        return items[p];
    }

    void append(int x)
    {
        if (full())
        {
            cout << "\nLista jest pelna!"; 
            return;
        }

        tail++;
        items[tail] = x;
        size++;
    }

    void preppend(int x)
    {
        if (full())
        {
            cout << "\nLista jest pelna!"; 
            return;
        }

        for (int i = getLast() +1; i > getFirst(); i--)
        {
            items[i] = items[i - 1];
        }

        items[head] = x;
        tail++;
        size++;
    }

    bool insert(int p, int x)
    {
        if (full())
        {
            cout << "\nLista jest pelna!";
            return false;
        }

        if (p < getFirst() || p > getLast() +1)
        {
            cout << "\nTaka pozycja nie istnieje!";
            return false;
        }

        for (int i = getLast() +1; i > p; i--)
        {
            items[i] = items[i - 1];
        }

        items[p] = x;
        tail++;
        size++;
        return true;
    }

    bool del(int p)
    {
        if (empty())
        {
            cout << "\nLista jest pusta!";
            return false;
        }

        if (p < getFirst() || p > getLast())
        {
            cout << "\nTaka pozycja nie istnieje!";
            return false;
        }

        for (int i = p; i < getLast(); i++)
        {
            items[i] = items[i + 1];
        }

        tail--;
        size--;
        return true;
    }

    void clear()
    {
        if (empty())
        {
            cout << "\nLista jest pusta!"; 
            return;
        }
        head = 0;
        tail = -1;
        size = 0;
    }

   friend ostream& operator<<(ostream& out, ArrayList& l)
    {
        for (int i = l.head; i <= l.tail; i++)
        {
            out << l.items[i] << " ";
        }

        out << "\n";

        return out;
    }

   int locate(int x)
   {
       if (empty())
       {
           cout << "\nLista jest pusta!";
           return -1;
       }
       
       for (int i = getFirst(); i <= getLast(); i++)
       {
           if (items[i] == x)  return i;
          
       }

       return -1;
   }

   bool deleteX(int x)
   {
       if (empty())
       {
           cout << "\nLista jest pusta!";
           return -1;
       }

       for (int i = getFirst(); i <= getLast(); i++)
       {
           if (items[i] == x)
           {
               del(i);
               return true;
           }
       }

       return false;
   }

   int deleteAllX(int x)
   {
       int k = 0;

       if (empty())
       {
           cout << "\nLista jest pusta!";
           return -1;
       }

       for (int i = getFirst(); i <= getLast(); i++)
       {
           if (items[i] == x)
           {
               k++;
               del(i);
               i--;
           }
       }

       return k;
   }

   bool concat(ArrayList& l)
   {
       if ((getCapacity() - getSize()) < l.getSize())
       {
           return false;
       }

       for (int i = l.getFirst(); i <= l.getLast(); i++)
       {
           append(l.items[i]);
       }
       return true;
   }

   ~ArrayList() {}

};

class SortedArrayList : public ArrayList
{

public:

    SortedArrayList(int c = 0)
        :ArrayList(c)
    {

    }

    SortedArrayList(ArrayList l)
    {
        head = l.getFirst();
        tail = l.getLast();
        size = l.getSize();
        capacity = l.getCapacity();
        items = new int[l.getCapacity()];
        for (int i = l.getFirst(); i <= l.getLast(); i++)
        {
            items[i] = l.retrieve(i);
        }
    }
    
    //quicksort
    void sortArrayList(int h, int t)
    {
        if (t <= h) return;

        int i = h - 1, j = t + 1,
            pivot = items[(h + t) / 2];

        while (1)
        {
            while (pivot > items[++i]);

            while (pivot < items[--j]);

            if (i <= j)
                swap(items[i], items[j]);
            else
                break;
        }

        if (j > h)
            sortArrayList(h, j);
        if (i < t)
            sortArrayList(i, t);
    }

    void insertSorted(int x)
    {
        if (full())
        {
            cout << "\nLista jest pelna!";
            return;
        }

        //sortArrayList(getFirst(), getLast());

        for (int i = getFirst(); i <= getLast(); i++)
        {
            if (items[i] >= x)
            {
                for (int j = getLast()+1; j > i; j--)
                {
                    items[j] = items[j - 1];
                }

                items[i] = x;
                tail++;
                size++;
                break;
           }
        }

    }

    ~SortedArrayList() {}
};

int main()
{

    //Zadanie 1
    cout << "Zadanie 1\n";
    ArrayList a(5);
    cout << endl << "empty(): [1] - " << a.empty();
    cout << endl << "full(): [0] - " << a.full();
    cout << endl << "getSize(): [0] - " << a.getSize();
    cout << endl << "append(4): [4]"; a.append(4); cout << "\n" << a;
    cout << "empty(): [0] - " << a.empty();
    cout << endl << "insert(1,8): [1] - " << a.insert(1, 8) << "\n" << a;
    cout << "append(1): "; a.append(1); cout << "\n" << a;
    cout << "preppend(5): "; a.preppend(5); cout << "\n" << a;
    cout << "insert(2,15): [1] - "; a.insert(2, 15); cout << " \n" << a;
    cout << "getNext(2): [3] - " << a.getNext(2);
    cout << endl << "getNext(4): [-1] - " << a.getNext(4);
    cout << endl << "empty(): [0] - " << a.empty();
    cout << endl << "full(): [1] - " << a.full();
    cout << endl << "getSize(): [5] - " << a.getSize();
    cout << endl << "getPrev(3): [2] - " << a.getPrev(3);
    cout << endl << a;
    cout << "retrieve(2): [15] - " << a.retrieve(2);
    cout << "del(1): " << a.del(1);
    cout << "\n" << a;
    cout << "Get prev" << a.getPrev(1);

    //Zadanie 2
    cout << "\n\nZadanie 2\n\n";
    ArrayList b(64);
    b.append(2);
    b.append(6);
    b.append(9);
    b.append(17);
    b.append(22);
    b.append(22);
    b.append(22);
    b.append(25);
    b.append(26);
    b.append(6);
    cout << b;
    cout << "locate(9): " << b.locate(9) << "\n";
    cout << "deleteX(6): " << b.deleteX(6) << "\n";
    cout << b;
    cout << "deleteAllX(22): " << b.deleteAllX(22) << "\n";
    cout << "b: " << b;
    cout << "a: " << a;
    cout << "concat(a): " << b.concat(a) << "\n";
    cout << b;

    cout << "\n\nZadanie 3\n\n";

    SortedArrayList c(b);

    cout << c;
    cout << "Sortowanie listy c: "; 
    c.sortArrayList(c.getFirst(), c.getLast());
    cout << c;
    cout << "insertSorted(20): ";
    c.insertSorted(20);
    cout << c;
    c.insertSorted(3);
    c.insertSorted(14);
    cout << c;

	return 0;
}