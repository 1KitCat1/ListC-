#include <iostream>
#include <vector>

using namespace std;

int myCeil(double rez) {
    if (rez == (int)rez) return (int)rez;
    else return (int)rez + 1;
}

template<typename T>
class ArrayList{
    int max;
    int last = -1;
    T* array;
public:
    ArrayList(int m = 10) {
        max = m;
        array = new T[max];
        last = -1;
    }
    ~ArrayList() {
        delete[] array;
    }
    void printList() {
        cout << '[';
        for (int i = 0; i <= last; ++i){
            cout << array[i] << (i == last ? "" : ", ");
        }
        cout << "]\n";
    }
    bool isFull() {
        return last == max - 1;
    }
    bool isEmpty() {
        return last == -1;
    }
    int size() {
        return last + 1;
    }
    int max_size() {
        return max;
    }
    void Sort() {
        for (int i = 0; i < last; i++) {
            for (int j = 0; j < last; j++) {
                if (array[j] > array[j + 1]) {
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
    void addItem(T item) {
        if (isFull()) {
            return;
        }
        else {
            /*for (int i = last; i >= 0; --i){
                array[i + 1] = array[i];
                if (array[i] <= item){
                    array[i + 1] = item;
                    break;
                }
            }
            last++;
            */
            array[++last] = item;
            Sort();
        }
    }
    bool delItems(T obj) {
        bool good = false;
        for (int i = 0; i <= last; i++) {
            if (array[i] == obj) {
                good = true;
                /*for (int j = i; j <= last; i++) {
                    array[j] = array[j + 1];
                }
                return i;
                last--;*/
                array[i] = array[last--];
                Sort();
                i--;
            }
        }
        if (good) return true;
        return false;
    }
    bool Search(T obj) {
        for (int i = 0; i <= last; i++) {
            if (array[i] == obj) return true;
        }
        return false;
    }
    void Replace(T obj1, T obj2) {
        int amountOf1 = 0;
        for (int i = 0; i <= last; i++) {
            if (array[i] == obj1) amountOf1++;
        }
        delItems(obj1);
        for (int i = 0; i < amountOf1; i++) {
            addItem(obj2);
        }
    }
    void Duplicate(T obj, int k) {
        int amountOfT = 0;
        for (int i = 0; i <= last; i++) {
            if (array[i] == obj) amountOfT++;
        }
        for (int i = 0; i < amountOfT; i++) {
            for (int j = 0; j < k; j++) {
                addItem(obj);
            }
        }
    }
    bool RecursiveSearch(int obj, int pos = 0) {
        if (pos == last + 1) return false;
        if (array[pos] == obj) return true;
        return RecursiveSearch(obj, ++pos);
    }
    T getElement(int i) {
        if (i > last) return -99999;
        return array[i];
    }
    bool delItem(T obj) {
        bool good = false;
        for (int i = 0; i <= last; i++) {
            if (array[i] == obj) {
                good = true;
                /*for (int j = i; j <= last; i++) {
                    array[j] = array[j + 1];
                }
                return i;
                last--;*/
                array[i] = array[last--];
                Sort();
                return true;
            }
        }
        return false;
    }
    void Intersection(ArrayList<T>& B) {
        vector<bool> vecB(B.size(), false);

        for (int i = 0; i < size(); i++) {
            bool good = false;
            for (int j = 0; j < B.size(); j++) {
                if (!vecB[j] && array[i] == B.getElement(j)) {
                    vecB[j] = true;
                    good = true;
                    break;
                }
            }
            if (!good) {
                delItem(array[i--]);
            }

        }
        
        /*
        for (int i = 0; i <= last; i++) {
            bool good = false;
            for (int j = 0; j < B.size(); j++) {
                if (!wasUsed[j] && B.getElement(j) == array[i]) {
                    wasUsed[j] = true;
                    good = true;
                    break;
                }
            }
            if (!good) {
                delItem(array[i]);
                i--;
            }
        }*/
    }
    void TrimToSize() {
        max = last + 1;
    }
    void delDuplicates() {
        for (int i = 1; i < size(); i++) {
            if (array[i] == array[i - 1]) {
                delItem(array[i]);
                i--;
            }
        }
    }
    void Union(ArrayList<T>& B) {
        for (int i = 0; i < B.size(); i++) {
            T item = B.getElement(i);
            addItem(item);
        }
        delDuplicates();
        //Sort();
    }
    void Merge(ArrayList<T>& B) {
        for (int i = 0; i < B.size(); i++) {
            T item = B.getElement(i);
            addItem(item);
        }
    }
    int SubsequencesSearch() {
        int amountOfSubsequences = 0;
        for (int i = 0; i < size(); i++) {
            amountOfSubsequences++;
            cout << "Subsequence " << array[i] << ". Length: ";
            int length = 1;
            while (i < size() && array[i + 1] == array[i]) {
                i++;
                length++;
            }
            cout << length << "\n";
        }
        return amountOfSubsequences;
    }
    void Difference(ArrayList<T>& B) {
        vector<bool> vecB(B.size(), false);

        for (int i = 0; i < size(); i++) {
            bool good = false;
            for (int j = 0; j < B.size(); j++) {
                if (!vecB[j] && array[i] == B.getElement(j)) {
                    vecB[j] = true;
                    good = true;
                    break;
                }
            }
            if (good) {
                delItem(array[i--]);
            }

        }

    }
    void Split(int n) {
        int sizeOfList = myCeil(size() / n);
        vector <ArrayList<T>> Arrays(n);
        for (int i = 0; i < n; i++) {
            ArrayList<T> temp(sizeOfList + 5);
            for (int j = 0; j < sizeOfList; j++) {
                temp.addItem(getElement(i * sizeOfList + j));
            }
        }
        //ArrayList<T>* = new ArrayList<T>[amountOfLists];
    }
};

template<typename T>
class UnsortedArrayList {
private:
    int max;
    int last = -1;
    T* array;
public:
    UnsortedArrayList(int n) {
        max = n;
        last = -1;
        array = new T[n];
    }
    ~UnsortedArrayList(){
        delete array;
    }
    int size() {
        return last + 1;
    }
    bool addItemUnsorted(int item) {
        if (last + 1 >= max) return false;
        array[++last] = item;
        return true;
    }
    void printList() {
        cout << '[';
        for (int i = 0; i <= last; ++i) {
            cout << array[i] << (i == last ? "" : ", ");
        }
        cout << "]\n";
    }
    T getElement(int i) {
        if (i > last) return -99999;
        return array[i];
    }
    void mergeUnsorted(UnsortedArrayList& B) {
        for (int i = 0; i < B.size(); i++) {
            addItemUnsorted(getElement(i));
        }
    }
    
};

int main(){
    //m Sorted
    ArrayList<int> m(30);
    m.addItem(1);
    m.addItem(1);
    m.addItem(2);
    m.addItem(2);
    m.SubsequencesSearch();
    //n Sorted
    ArrayList<int> n(5);
    n.addItem(1);
    n.addItem(2);
    n.addItem(1);
    //
    //m.Duplicate(2, 2);
    //m.PrintList();
    m.Difference(n);
    n.printList();
    m.printList();
    //cout << m.RecursiveSearch(3);
    m.TrimToSize();
    
    //A Unsorted;
    UnsortedArrayList<int> A(20);
    A.addItemUnsorted(2);
    A.addItemUnsorted(6);

    //B Unsorted
    UnsortedArrayList<int> B(20);
    B.addItemUnsorted(3);
    B.addItemUnsorted(4);
    //
    A.mergeUnsorted(B);
    A.printList();
    
}