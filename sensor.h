#ifndef PROJET2_SENSOR_H
#define PROJET2_SENSOR_H
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstring>

class Server;

class scheduler { // Classe qui gère le programme
public:
    void run(); //Fonction principale
    void son(Server &); //Fonction qui gère le capteur de son
    void temperature(Server &); //Fonction qui gère le capteur de température
    void lumiere(Server &); //Fonction qui gère le capteur de lumière
    void humidite(Server &); //Fonction qui gère le capteur d'humidité
    void entre(Server &); //Fonction qui gère l'entrée des valeurs par l'utilisateur
};


class Server{ // Classe qui gère les valeurs des capteurs et les écritures dans les fichiers
private:
    bool consolActivation; // Booléen qui permet d'activer ou non l'affichage dans la console
    bool logActivation; // Booléen qui permet d'activer ou non l'écriture dans les fichiers
    int sound; // Valeur du capteur de son
    float temperature; // Valeur du capteur de température
    bool light; // Valeur du capteur de lumière
    float humidity; // Valeur du capteur d'humidité
    bool soundSensor{}; // Booléen qui permet d'activer ou non le capteur de son
    bool temperatureSensor{}; // Booléen qui permet d'activer ou non le capteur de température
    bool humiditySensor{}; // Booléen qui permet d'activer ou non le capteur d'humidité
    bool lightSensor{}; // Booléen qui permet d'activer ou non le capteur de lumière
    int intervalSound; // Intervalle de temps entre deux prises de valeurs du capteur de son
    int intervalTemperature; // Intervalle de temps entre deux prises de valeurs du capteur de température
    int intervalLight; // Intervalle de temps entre deux prises de valeurs du capteur de lumière
    int intervalHumidity; // Intervalle de temps entre deux prises de valeurs du capteur d'humidité
public:
    // Constructeurs, destructeur et opérateurs
    Server():consolActivation(false),logActivation(false),sound(0),temperature(0),light(false),humidity(0),soundSensor(false),temperatureSensor(false),humiditySensor(false),lightSensor(false),intervalSound(10),intervalTemperature(10),intervalLight(10),intervalHumidity(10){}
    Server(const Server &S);
    ~Server(){}
    Server& operator=(const Server& S); // Opérateur d'affectation
    Server& operator<<(const Server& S);
    template<class T> void fileWrite(std::string name_, T value) const; // Fonction qui écrit dans les fichiers
    void consolWrite(const string&) const ; // Fonction qui écrit dans la console la valeur d'un capteur
    void consolWrite() const; // Fonction qui écrit dans la console les valeurs de tous les capteurs
    friend void scheduler::run();
    friend void scheduler::son(Server &);
    friend void scheduler::temperature(Server &);
    friend void scheduler::lumiere(Server &);
    friend void scheduler::humidite(Server &);
    friend void scheduler::entre(Server &);
    void printvalue(const string& ) const; // Fonction qui écrit dans la console et dans les logs la valeur d'un capteur
};


template <class T>
class sensor {
protected:
    T valSensor; // Valeur du capteur
public:
    // Constructeurs, destructeur et opérateurs
    sensor();
    sensor(T val):valSensor(val){}
    sensor(const sensor &S):valSensor(S.valSensor){}
    virtual ~sensor(){} // Destructeur virtuel
    virtual void printSensorValue() const; // Fonction qui écrit dans la console la valeur du capteur
    virtual T aleaSensorValue()=0; // Fonction qui génère une valeur aléatoire pour le capteur

};

class soundSensor: public sensor<int>{ // Classe qui gère le capteur de son
public:
    soundSensor():sensor<int>(){}
    soundSensor(int val):sensor<int>(val){}
    soundSensor(const soundSensor &S):sensor<int>(S){}
    virtual ~soundSensor(){}
    void printSensorValue() const;
    int aleaSensorValue(); // Fonction qui génère une valeur aléatoire de type int pour le capteur
};

class temperatureSensor: public sensor<float>{ // Classe qui gère le capteur de température
public:
    temperatureSensor():sensor<float>(){}
    temperatureSensor(float val):sensor<float>(val){}
    temperatureSensor(const temperatureSensor &S):sensor<float>(S){}
    virtual ~temperatureSensor(){}
    void printSensorValue() const ;
    float aleaSensorValue(); // Fonction qui génère une valeur aléatoire de type float pour le capteur
};

class humiditySensor: public sensor<float>{ // Classe qui gère le capteur d'humidité
public:
    humiditySensor():sensor<float>(){}
    humiditySensor(float val):sensor<float>(val){}
    humiditySensor(const humiditySensor &S):sensor<float>(S){}
    virtual ~humiditySensor(){}
    void printSensorValue() const ;
    float aleaSensorValue(); // Fonction qui génère une valeur aléatoire de type float pour le capteur
};

class lightSensor: public sensor<bool>{ // Classe qui gère le capteur de lumière
public:
    lightSensor():sensor<bool>(){}
    lightSensor(bool val):sensor<bool>(val){}
    lightSensor(const lightSensor &S):sensor<bool>(S){}
    virtual ~lightSensor(){}
    void printSensorValue() const;
    bool aleaSensorValue(); // Fonction qui génère une valeur aléatoire de type bool pour le capteur
};

int verifnumber(string &number) { // Fonction qui vérifie que l'utilisateur entre bien un nombre entre 0 et 10
    int value;
    while ((number[0] <= '0' || number[0] > '9') && number.size() != 1) {
        cout << "Please enter a number between 0 and 10" << endl;
        cin >> number;
    }
    value = number[0] - '0';
    return value;
}

void verifYesNo(string &answer){ // Fonction qui vérifie que l'utilisateur entre bien Y ou N
    while (answer[0] != 'Y' && answer[0] != 'N' && answer[0] != 'y' && answer[0] != 'n' || answer.size() != 1) {
        fflush(stdin);
        cout << "Please answer by Y or N" << endl;
        cin >> answer;
    }
}


#endif //PROJET2_SENSOR_H
