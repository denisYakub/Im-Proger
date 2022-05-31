#include <iostream>
#include <memory>
#include <cmath>

#include "bdd.h"

using namespace std;

#define N 9 
#define M 4 
#define K 21

const int LOG_N = static_cast<int>(std::ceil(std::log2(N))); 
const std::size_t N_SQRT = static_cast<std::size_t>(sqrt(N)); 
const std::size_t N_VAR = N * M * LOG_N;

auto var = std::make_unique<char[]>(N_VAR);

enum class Neighbour {
    Up,
    Right
};

void fun(char* varset, int size);
void init(bdd p[M][N][N]);

bdd constant_1(const bdd p[M][N][N], const int proprertyNumber, const int objectNumber, const int proprertyValue);
bdd constant_2(const bdd p[M][N][N], const int proprertyNumber, const int proprertyValue, const int proprertyNumber1, const int proprertyValue1);
bdd constant_3(const bdd p[M][N][N], enum Neighbour value, const int proprertyNumber, const int proprertyValue, const int proprertyNumber1, const int proprertyValue1);
bdd constant_4(const bdd p[M][N][N], const int proprertyNumber, const int proprertyValue, const int proprertyNumber1, const int proprertyValue1);
void constant_5(bdd& tree, const bdd p[M][N][N]);
bdd constant_6(const bdd p[M][N][N]);
bdd constant_7(const bdd p[M][N][N]);

int main()
{
    bdd_init(1000000, 100000);
    bdd_setcacheratio(100); 
    bdd_setvarnum(N_VAR);
    bdd p[M][N][N];

    init(p);

    bdd task = bddtrue;

    //вариант № 2: n1 = 2, n2 = 3, n3 = 4, n4 = 5

    //ограничения n1
    task &= constant_1(p, 0, 2, 0);
    task &= constant_1(p, 2, 0, 5);

    //5 дополнительных ограничений для n1
    task &= constant_1(p, 1, 8, 0);
    task &= constant_1(p, 0, 3, 5);
    task &= constant_1(p, 2, 4, 8);
    task &= constant_1(p, 3, 5, 5);
    task &= constant_1(p, 2, 6, 0);

    //ограничения n2
    task &= constant_2(p, 0, 0, 2, 3);
    task &= constant_2(p, 2, 5, 3, 7);
    task &= constant_2(p, 1, 0, 2, 7);

    //6 дополнительных ограничений для n2
    task &= constant_2(p, 0, 5, 2, 2);
    task &= constant_2(p, 2, 0, 1, 3);
    task &= constant_2(p, 3, 3, 2, 4);
    task &= constant_2(p, 1, 4, 2, 1);
    task &= constant_2(p, 3, 7, 1, 2);
    task &= constant_2(p, 2, 3, 3, 8);

    //ограничения n3                     
    task &= constant_3(p, Neighbour::Right, 2, 8, 1, 5);
    task &= constant_3(p, Neighbour::Right, 0, 1, 1, 0);
    task &= constant_3(p, Neighbour::Up, 3, 1, 2, 5);
    task &= constant_3(p, Neighbour::Up, 0, 6, 2, 1);

    //1 дополнительных ограничений для n3
    task &= constant_3(p, Neighbour::Up, 3, 2, 1, 1);

    //ограничения n4
    task &= constant_4(p, 3, 7, 0, 3);
    task &= constant_4(p, 3, 6, 1, 6);
    task &= constant_4(p, 3, 1, 1, 7);
    task &= constant_4(p, 2, 0, 1, 8);
    task &= constant_4(p, 0, 2, 1, 5);

    //1 дополнительных ограничений для n4
    task &= constant_4(p, 0, 8, 3, 1);

    task &= constant_6(p);
    task &= constant_7(p);

    constant_5(task, p);

    std::size_t satcount = static_cast<std::size_t>(bdd_satcount(task));

    std::cout << satcount << " solutions:\n" << std::endl; //вывод решений 

    if (satcount)
    {
        bdd_allsat(task, fun); 

    }

    bdd_done();
}

void print()
{
    for (size_t i = 0; i < N; ++i)
    {
        std::cout << i << ": ";

        for (size_t j = 0; j < M; ++j)
        {
            int J = i * M * LOG_N + j * LOG_N;
            int num = 0;

            for (size_t k = 0; k < LOG_N; ++k)
            {
                num += static_cast<size_t>(var[J + k] << k);
            }

            std::cout << num << ' ';
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
void build(char* varset, unsigned n, unsigned I)
{
    if (I == n - 1)
    {
        if (varset[I] >= 0)
        {
            var[I] = varset[I];
            print();
            return;
        }
        var[I] = 0;
        print();
        var[I] = 1;
        print();
        return;
    }
    if (varset[I] >= 0)
    {
        var[I] = varset[I];
        build(varset, n, I + 1);
        return;
    }
    var[I] = 0;
    build(varset, n, I + 1);
    var[I] = 1;
    build(varset, n, I + 1);
}
void fun(char* varset, int size)
{
    build(varset, size, 0);
}

void init(bdd p[M][N][N])
{
    std::size_t I = 0;

    for (std::size_t i = 0; i < N; ++i)
    {
        for (std::size_t j = 0; j < N; ++j)
        {
            for (std::size_t z = 0; z < M; ++z)
            {
                p[z][i][j] = bddtrue;

                for (std::size_t k = 0; k < LOG_N; ++k)
                {
                    p[z][i][j] &= ((j >> k) & 1) ? bdd_ithvar(I + LOG_N * z + k) : bdd_nithvar(I + LOG_N * z + k);
                }
            }
        }

        I += LOG_N * M;
    }
}

bdd constant_1(const bdd p[M][N][N], const int proprertyNumber, const int objectNumber, const int proprertyValue)
{
    return p[proprertyNumber][objectNumber][proprertyValue];
}

bdd constant_2(const bdd p[M][N][N], const int proprertyNumber, const int proprertyValue, const int proprertyNumber1, const int proprertyValue1)
{
    bdd tree = bddtrue;

    for (size_t i = 0; i < N; ++i)
    {
        tree &= !(p[proprertyNumber][i][proprertyValue] ^ p[proprertyNumber1][i][proprertyValue1]);
    }
    return tree;
}

bdd constant_3(const bdd p[M][N][N], enum Neighbour value, const int proprertyNumber, const int proprertyValue, const int proprertyNumber1, const int proprertyValue1)
{
    bdd tree = bddtrue;

    switch (value)
    {
    case Neighbour::Right:
        for (size_t i = 0; i < N; ++i)
        {
            if ((i + 1) % N_SQRT != 0)
            {
                tree &= !(p[proprertyNumber][i][proprertyValue] ^ p[proprertyNumber1][i + 1][proprertyValue1]);
            }
        }
        break;
    case Neighbour::Up:
        for (std::size_t i = N_SQRT; i < N; ++i)
        {
            tree &= !(p[proprertyNumber][i][proprertyValue] ^ p[proprertyNumber1][i - N_SQRT][proprertyValue1]);
        }
        break;
    }
    
    return tree;
}

bdd constant_4(const bdd p[M][N][N], const int proprertyNumber, const int proprertyValue, const int proprertyNumber1, const int proprertyValue1)
{
    return constant_3(p, Neighbour::Up, proprertyNumber, proprertyValue, proprertyNumber1, proprertyValue1) |
        constant_3(p, Neighbour::Right, proprertyNumber, proprertyValue, proprertyNumber1, proprertyValue1);;
}
void constant_5(bdd& tree, const bdd p[M][N][N])
{
    for (std::size_t m = 0; m < M; ++m)
    {
        for (std::size_t i = 0; i < N - 1; ++i)
        {
            for (std::size_t j = i + 1; j < N; ++j)
            {
                for (std::size_t k = 0; k < N; ++k)
                {
                    tree &= p[m][i][k] >> !p[m][j][k];
                }
            }
        }
    }
}

bdd constant_6(const bdd p[M][N][N])
{
    bdd tree = bddtrue;

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t k = 0; k < M; ++k)
        {
            bdd temp = bddfalse;

            for (size_t j = 0; j < N; ++j)
            {
                temp |= p[k][i][j];
            }

            tree &= temp;
        }
    }

    return tree;
}

bdd constant_7(const bdd p[M][N][N])
{
    bdd task = bddtrue;

    for (int i = 0; i < N; ++i)
    {
        bdd temp = bddfalse;

        for (int j1 = 0; j1 < N; ++j1)
        {
            for (int j2 = 0; j2 < N; ++j2)
            {
                for (int j3 = 0; j3 < N; ++j3)
                {
                    for (int j4 = 0; j4 < N; ++j4)
                    {
                        if (j1 + j2 + j3 + j4 <= K)
                        {
                            temp |= (p[0][i][j1] & p[1][i][j2] & p[2][i][j3] & p[3][i][j4]);
                        }
                    }
                }
            }
        }

        task &= temp;
    }

    return task;
}