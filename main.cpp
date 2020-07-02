#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>
namespace Support
{
    class timer
    {
    public:
        timer(){
            start = std::chrono::steady_clock::now();
        };

        float stop_seconds()
        {
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            return elapsed_seconds.count();
        }

    private:
        std::chrono::steady_clock::time_point start;
    };

    std::vector<int> generateVector(int min,int max, int size)
    {
        std::vector<int> buf;
        buf.reserve(size);
        srand(time(NULL));
        if(min>max)
            throw std::runtime_error("wtf bro, min should be smaller than max");

        for(int x=0;x<size;x++)
            buf.push_back(min+rand()%(max-min));
        return buf;
    }
}

int linearSearch(std::vector<int>& to_search, int value)
{
    Support::timer t;
    int compares=0;
    for(int x=0;x<to_search.size();x++)
    {
        compares++;
        if(to_search[x]==value)
        {
            std::cout << "Linear Search for " << value<< "->" << "Length:" << to_search.size()<< " Time:" << t.stop_seconds()<<" Compares:"<<compares<<std::endl;
            return x;
        }
    }
    return to_search.size();
}


namespace Sort
{
    void exchangeSort(std::vector<int>& to_sort) //bubblesort
    {
        Support::timer t;
        int vergleiche =0;
        int swaps =0;
        int i,j;
        for(i=0;i<to_sort.size()-1;i++)
        {
            for(j=to_sort.size()-2;j>=i;j--)
            {
                vergleiche++;
                if(to_sort[j]>to_sort[j+1])
                {
                    swaps++;
                    std::swap(to_sort[j],to_sort[j+1]);
                }
            }
        }
        float buf =  t.stop_seconds();

        std::cout << "Exchange Sort->"<< "Lenght:" << to_sort.size() << " Time:" << buf << " Compares:" << vergleiche << " Swaps:"<<swaps<<std::endl;
    }

    void insertion_sort(std::vector<int>& to_sort)
    {
        Support::timer t;
        int compares=0;
        int swaps=0;
        for(int i=1;i<to_sort.size();i++)
        {
            int buffer = to_sort[i];
            int j=i;
            while (j>0&&buffer<to_sort[j-1]) //ein key vergleich
            {
                compares++;
                swaps++;
                to_sort[j]=to_sort[j-1];
                j--;
            }
            to_sort[j]=buffer;
        }
        float buf =  t.stop_seconds();

        std::cout<< "Insertion Sort->" << "Lenght:" << to_sort.size()<< " Time:" << buf << " Compares:" << compares << " Swaps:"<<swaps<<std::endl;
    }

    void selection_sort(std::vector<int>& to_sort)
    {
        Support::timer t;
        int compares=0;
        int swaps=0;
        int imin = 0;
        for(int iterator=0;iterator<to_sort.size()-1;iterator++)
        {
            imin=iterator;
            for(int j=iterator+1;j<to_sort.size();j++)
            {
                compares++;
                if(to_sort[j]<to_sort[imin])
                {
                    imin=j;
                }
            }
            swaps++;
            std::swap(to_sort[iterator],to_sort[imin]);
        }
        float buf =  t.stop_seconds();
        std::cout << "Selection Sort->" <<"Lenght:" << to_sort.size()<< " Time:" << buf << " Compares:" << compares << " Swaps:"<<swaps<<std::endl;
    }

    class Quicksort
    {
    public:
        /*
         * Im Allgemeinen O(nlogn) Vergleiche und Recordbewegungen
         * Mittlerer Fall: wächst genauso schnell wie O(nlogn)
         * ist leicht zu implememtieren
         * im schlechtesten Fall n² aber im Median besser als n², im allgemeinen nlogn
         */
        enum class PivotType
        {
            Mean,Median
        };
        Quicksort(std::vector<int>& i_to_sort,PivotType type):to_sort(i_to_sort){
            Support::timer t;
            m_type = type;
            Quicksort_table(0,to_sort.size()-1);
            float buf = t.stop_seconds();
            std::cout << "Quick Sort->";
            switch (m_type) {
                case PivotType::Median:
                    std::cout << "Median->";
                    break;
                case PivotType::Mean:
                    std::cout << "Mean->";
                    break;
            }
            std::cout <<"Lenght:" << to_sort.size()<< " Time:" << buf << " Compares:" << compares << " Swaps:"<<swaps<<std::endl;
        };

    private:
        void Mean(int l,int r)
        {
            int m=(l+r)/2;
            std::swap(to_sort[m],to_sort[r]);
            swaps++;
        }

        int Median(int l,int r)
        {
            int buf=0;
            for(int x=l;x<r;x++)
                buf+=to_sort[x];
            return buf/(r-l);
        }


        int Partition(int left,int right)
        {
            int iterator = left-1;
            int j = right;

            switch (m_type) {
                case PivotType::Median:
                    Median(left,right);
                    break;
                case PivotType::Mean:
                    Mean(left,right);
                    break;
            }

            while (iterator<j)
            {
                while (to_sort[++iterator]<=to_sort[right])
                {
                    if(iterator==right)
                        break;
                    compares++;
                }

                while (to_sort[--j]>to_sort[right])
                {
                    if(j==left)
                        break;
                    compares++;
                }

                if(iterator<j)
                {
                    std::swap(to_sort[iterator],to_sort[j]);
                    swaps++;
                }

            }
            std::swap(to_sort[right],to_sort[iterator]);
            swaps++;
            return iterator;
        }

        void Quicksort_table(int l,int r)
        {
            int m = Partition(l,r);
            if(l<m-1)
                Quicksort_table(l,m-1);
            if(m+1<r)
                Quicksort_table(m+1,r);
        }
        std::vector<int>& to_sort;
        int compares =0;
        int swaps =0;
        PivotType m_type;
    };
}

namespace Tree
{
    class TreeNode
    {
    public:
        TreeNode(int r): value(r){};
        int value;
        TreeNode *left= nullptr;
        TreeNode *right= nullptr;
        int path;
        void setSuccessor(TreeNode* l,TreeNode* r);
    };

    class TPosition
    {
    public:
        TPosition(){p=nullptr;}
        bool TPos() {return p!= nullptr;}
        bool TPos(TPosition pos)
        {
            return (pos.p==p);
        };
        TreeNode* p;
    };

    class BinaryTree
    {
    public:
        BinaryTree();
        ~BinaryTree(){
            if(t)
                deleteTree();
        };
        TPosition Root()
        {
            TPosition pos;
            pos.p=t;
            return pos;
        };
        TPosition Left(TPosition pos){
            TPosition posl;
            if(pos.p)
                posl.p=pos.p->left;
            return posl;
        };
        TPosition Right(TPosition pos){
            TPosition posr;
            if(pos.p)
                posr.p=pos.p->right;
            return posr;
        };


        void insertRoot(int r){
            if(!t)
                t=new TreeNode(r);
        };


        void insertLeft(int r, TPosition pos){
            if(t== nullptr)
                return;
            TreeNode *q = new TreeNode(r);
            q->right = pos.p->left;
            pos.p->left = q;
        };
        void insertRight(int r, TPosition pos){
            if(t== nullptr)
                return;
            TreeNode *q = new TreeNode(r);
            q->left = pos.p->right;
            pos.p->right = q;
        };


        void deleteTree(){
            delTree(Root());
            t= nullptr;
        };
        TPosition deleteNode(TPosition node){
            //TODO göhner brudi was los ? wo isch der laden
        };
        int getNode(TPosition pos){
            int r;
            if(pos.p)
                return pos.p->value;
            else
                return r;
        };
        void setNode(int &r, TPosition pos){
            if(pos.p)
                pos.p->value=r;
        };

        void preorder(TPosition pos)
        {
            if(pos.TPos())
            {
                visit(getNode(pos));
                preorder(Left(pos));
                preorder(Right(pos));
            }
        }

        void inorder(TPosition pos)
        {
            if(pos.TPos())
            {
                inorder(Left(pos));
                visit(getNode(pos));
                inorder(Right(pos));
            }
        }

        void postorder(TPosition pos)
        {
            if(pos.TPos())
            {
                postorder(Left(pos));
                postorder(Right(pos));
                visit(getNode(pos));
            }
        }

        unsigned numnodes(TPosition pos)
        {
            if(pos.TPos())
                return numnodes(Left(pos))+numnodes(Right(pos))+1;
            else
                return 0;
        }

        void visit(int r)
        {
            std::cout << r << " ";
        }

    private:
        TreeNode *t;
        void delTree(TPosition pos){
            if(pos.TPos())
                delTree(Left(pos));
                delTree(Right(pos));
                delete pos.p;
        };
    };
}



int main() {
    auto to_sort = Support::generateVector(0,100000,20000);

    auto exch = to_sort;//copy
    Sort::exchangeSort(exch); //bubblesort

    auto insert = to_sort;
    Sort::insertion_sort(insert);

    auto selection = to_sort;
    Sort::selection_sort(selection);

    auto quick1 = to_sort;
    Sort::Quicksort sort(quick1,Sort::Quicksort::PivotType::Median);

    auto quick2 = to_sort;
    Sort::Quicksort sort2(quick2,Sort::Quicksort::PivotType::Mean);

    auto quick_std = to_sort;
    Support::timer t;
    std::sort(quick_std.begin(),quick_std.end());
    std::cout << "Std_sort time:" << t.stop_seconds()<<std::endl;
    linearSearch(to_sort,to_sort[rand()%to_sort.size()]);
}
