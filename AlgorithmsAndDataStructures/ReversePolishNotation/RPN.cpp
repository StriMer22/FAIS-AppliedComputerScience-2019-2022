//
// Created by Dmytro on 1/7/2021.
//
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

// Zwracamy priorytet operacji
int prior(char& in){
    if(in == '+' || in == '-')
        return 1;
    else if(in == '*' || in == '/')
        return 2;
    else if(in == '^')
        return 3;
    else
        return 0;
}

// Czy to jest liczba
bool is_digit(char& in){
    return (in >= '0' && in <= '9');
}

// Czy to jest zmienna
bool is_var(char& in){
    return ((in >= 'a' && in <= 'z') ||
            (in >= 'A' && in <= 'Z'));
}

// Czy to jest operacja
bool is_oper(char& in){
    return (in == '+' || in == '-' ||
            in == '*' || in == '/' ||
            in == '^');
}

queue<char> to_revpol(const string& in){
    stack<char> stk;// tworzymy stos dla zachowania tymczasowych operacji
    queue<char> gen;// tworzymy kolejke dla wszystkeigo
    bool clbr = false;
    char i;
    for(char j : in){
        i = j;
        if(i == '.' || i == ',')// sprawdzania dla liczb z przecinkiem: np. 0.2
            gen.push(i);
        else if(is_digit(i)){
            if((!gen.empty() && is_var(gen.back())) || clbr){ //jeżeli z gen cos jest i to jest zmienna lub flaga zamkniętego nawiasu została podniesiona, to...
                stk.push('^'); gen.push(';'); clbr = false;} //jest to konieczne, aby nie pisać znaku stopnia po zmiennych i nawiasach, na przykład, x2 == x^2 lub (1+2)2 == (1+2)^2
            gen.push(i);
        }
        else if(is_var(i)){
            if(!gen.empty() && is_digit(gen.back())){
                stk.push('*'); gen.push(';'); } //5x == 5*x,
            gen.push(i);
        }
        else if(is_oper(i)){
            if(!stk.empty()){
                if(prior(i) == prior(stk.top())){ //jeżeli operacji maja ten sam priorytet
                    gen.push(stk.top()); //wyciagamy poprzednia operacje
                    stk.top() = i;//i zamieniamy
                }
                else if(prior(i) < prior(stk.top())){ //jeżeli priorytet jest nizszy
                    while(!stk.empty() && stk.top() != '('){ // wyciagamy wszystko przed nawiasem otwierającym lub do momentu, gdy stos będzie pusty
                        gen.push(stk.top());
                        stk.pop();
                    }
                    stk.push(i);
                }
            }
            if(stk.empty() || prior(i) > prior(stk.top())){ // jeśli stos jest pusty lub priorytet ostatniej operacji jest mniejszy niż bieżący
                if(!gen.empty() && is_digit(gen.back()) || is_var(gen.back())) // jeśli ostatnią rzeczą w gen jest zmienna lub liczba
                    gen.push(';'); // to musimy umieścić znak rozdzielający
                else if(((!stk.empty() && stk.top() == '(') || gen.empty()) && i == '-') // jeśli stos nie jest pusty i ostatnią rzeczą, która została do niego zapisana, był otwarty nawias, lub w ogóle nie mamy nic, a i == -, to wstawiam znak _
                    gen.push('_'); // jeśli ostatnim w gen nie jest _, co możemy po prostu napisać => to jest jakaś operacja
                if(gen.back() != '_')
                    stk.push(i);
            }
        }
        else if(i == '('){ // jeśli nie mamy liczby, ani zmiennej ani operacji, ale otwarty nawias
            if(!gen.empty() && (is_digit(gen.back()) || is_var(gen.back()))){ // jeśli ostatnią rzeczą w gen jest zmienna lub liczba
                gen.push(';'); // umieszczamy znak ograniczajacy, a w stos zapisujemy *
                stk.push('*');
            }
            stk.push(i);
        }
        else if(i == ')'){ // jeśli mamy zamknięty nawias, powinniśmy zwolnić wszystkie operacje od stk do gen
            clbr = true;
            while(!stk.empty() && stk.top() != '('){
                gen.push(stk.top());
                stk.pop();
            }
            if(!stk.empty())
                stk.pop();
        }
    }

    while(!stk.empty()){ // jezeli cos zostanie w stosie
        gen.push(stk.top());
        stk.pop();
    }
    return gen;
}

double calc(queue<char> in){
    stack<double> res; // tymczasowe przechowywanie wartości
    map<string, double> mem; // aby nie żądać dwukrotnie tej samej zmiennej
    string var_buf; // bufor dla zmiennych
    bool minus = false, op = false; // flagi dla minus lub dla operacji
    size_t fl = 0; // zmienna do poprawnego wprowadzania wartości zmiennoprzecinkowych
    double temp;

    res.push(0.0); // dodajemy jedno znaczenia
    while(!in.empty()){ // dopóki kolejka nie będzie pusta
        if(in.front() == '_'){ // jeśli jest znak _, to wystąpiło: -3 + 2 lub 5 * (-4 + 3) itd.
            minus = true;
            in.pop(); // usuwamy elemnt
        }
        else if(is_digit(in.front())){
            if(op) { res.push(0.0); op = false; } // jeśli była jakaś operacja i teraz musimy wpisać nową wartość, to dodajemy pamięć i obniżamy flagę
            while(!in.empty() && is_digit(in.front())){
                if(!(in.front() == '0' && res.top() == 0.0)){// aby nie pomnożyć 0 przez 10 i nie dodawać (48 - 48)
                    if(fl == 0){ // gdy mamy zwykłą liczbę całkowitą
                        res.top() = res.top() * 10 + in.front() - 48;
                    }else{
                        temp = in.front() - 48; // konwersja char w int/float
                        for(size_t i = 0; i < fl; i++)
                            temp /= 10;
                        res.top() += temp;// i po prostu dodajemy do aktualnego
                        fl++;
                    }
                }
                in.pop();
                if(!in.empty() && in.front() == '.'){ // jeśli to jest kropka, a kolejka nie jest pusta, to
                    fl = 1; // ustawiamy licznik na 1
                    in.pop();
                }
            }
            fl = 0; // po odczytaniu liczby zresetuj licznik
        }
        else if(is_var(in.front())){
            if(op) { res.push(0.0); op = false; } // jeśli wcześniej była operacja, a teraz musimy wprowadzić nową wartość, to alokujemy pamięć
            var_buf.clear();
            do{ // dodaje nazwę zmiennej do bufora. I w pętli, abyś mozna było pisać zmienne więcej niż jedną literą
                var_buf.push_back(in.front());
                in.pop();
            }while(!in.empty() && is_var(in.front()));
            if(mem.find(var_buf) != mem.end()){
                res.top() = mem[var_buf]; //przypisz zapamiętaną wartość na topie
            }else{
                cout << "Please enter the variable \'" << var_buf << "\': ";
                cin >> res.top();
                mem[var_buf] = res.top();
            }
        }
        else if(in.front() == ';' || is_oper(in.front())){ // jeśli mamy operację
            if(minus){ // jeśli ustawiona jest flaga minus
                minus = false;
                res.top() = -res.top(); // pomnóż aktualną wartość przez -1
            }
            if(in.front() == ';'){ //dodajemy pamięć
                res.push(0.0);
                in.pop();
            }
            else if(res.size() > 1){ // jeśli mamy coś w stosie
                temp = res.top(); // zapisujemy ostatnie znaczenia w temp
                res.pop(); //usuwamy go ze stosu
                switch(in.front()){ // patrzymy co to jest i wykonujemy operacje
                    case '+':
                        res.top() += temp;
                        break;
                    case '-':
                        res.top() -= temp;
                        break;
                    case '*':
                        res.top() *= temp;
                        break;
                    case '/':
                        res.top() /= temp;
                        break;
                    case '^':
                        res.top() = pow(res.top(), temp);
                }
                op = true;
                in.pop();
            }
        }
    }
    if(res.size() > 1){
        cout << "something went wrong!";
        while(!res.empty()){
            cout << res.top() << ' ';
            res.pop();
        }
        return 0.0;
    }
    return res.top();
}

template <class T>
ostream& operator<<(ostream& out, queue<T> cs){
    while(cs.empty() != true){
        out << cs.front();
        cs.pop();
    }
    return out;
}

int main(){
    string in;
    queue<char> gen;
    cout << "Enter an expression: ";
    cout << "For example: (a-(b+c*d)/e) \n";
    getline(cin, in);
    gen = to_revpol(in);
    cout << "Result of the function to_revpol: " << gen << endl;
    cout << calc(gen);
}

