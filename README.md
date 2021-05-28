# Vector

## Greičio palyginimai

### push_back() int palyginimas

| Konteineris\Greitis | 10000 | 100000 | 1000000 | 10000000 | 100000000 |
|---------------------|-------|--------|---------|----------|-----------|
| Vector              | 0s    | 0.002s | 0.015s  | 0.178s   | 1.49s     |
| std::vector         | 0s    | 0.003s | 0.0159s | 0.157s   | 1.37s     |

### skaičiuoklės greičio palyginimas

| Konteineris\Greitis |  10000  | 100000 | 1000000 | 
|---------------------|---------|--------|---------|
| Vector              | 0.001s  | 0.011s | 0.1s    | 
| std::vector         | 0.0009s | 0.012s | 0.104s  |

## Funkcijos 

* push_back()
```
Vector<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);

    std::cout << test[0] << test[1] << test[2] << test[3];
```
* Ats.:
```
1234
```
* cout norimas elementas
```
Vector<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);

    std::cout << test[1] << test[3];
```
* Ats.:
```
24
```
* insert()
```
Vector<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);
    test.insert(test.begin()+2, 5);

    std::cout << test[0] <<test[1] << test[2] << test[3] << test[4];
```
* Ats.:
```
12534
```
* pop_back()
```
Vector<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);
    test.pop_back();    

    std::cout << test[0] <<test[1] << test[2] << test[3] << test[4];
```
* Ats.:
```
12340
```
* erase()
```Vector<int> test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    test.push_back(4);  
    test.erase(test.begin());

    std::cout << test[0] <<test[1] << test[2];
```
* Ats.:
```
234
```
