#include "sensor.h"

/**********************************************************/

template<class T>
sensor<T>::sensor() { // Constructeur par défaut
    if (typeid(T) == typeid(int)) { // Si le type de T est int
        valSensor = 0;
    } else if (typeid(T) == typeid(double)) { // Si le type de T est double
        valSensor = 0.0;
    } else if (typeid(T) == typeid(bool)) { // Si le type de T est bool
        valSensor = false;
    }
}

template<class T>
void sensor<T>::printSensorValue() const { // Fonction qui écrit dans la console la valeur du capteur
    cout<< "Sensor value: " << valSensor << endl;
}


/**********************************************************/

void soundSensor::printSensorValue() const { // Fonction qui écrit dans la console la valeur du capteur son
    cout<< "Sensor sound value: " << valSensor << endl;
}

void temperatureSensor::printSensorValue() const { // Fonction qui écrit dans la console la valeur du capteur température
    cout<< "Sensor temperature value: " << valSensor << endl;
}

void humiditySensor::printSensorValue() const { // Fonction qui écrit dans la console la valeur du capteur humidité
    cout<< "Sensor humidity value: " << valSensor << endl;
}

void lightSensor::printSensorValue() const { // Fonction qui écrit dans la console la valeur du capteur lumière
    cout<< "Sensor light value: " << valSensor << endl;
}

int soundSensor::aleaSensorValue() { // Fonction qui génère une valeur aléatoire de type int pour le capteur son
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100); // On génère un nombre aléatoire entre 0 et 100
    valSensor = dis(gen);
    return valSensor;
}

float temperatureSensor::aleaSensorValue() { // Fonction qui génère une valeur aléatoire de type float pour le capteur température
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 100); // On génère un nombre réel aléatoire entre 0 et 100
    valSensor = dis(gen);
    return valSensor;
}

float humiditySensor::aleaSensorValue() { // Fonction qui génère une valeur aléatoire de type float pour le capteur humidité
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 100); // On génère un nombre réel aléatoire entre 0 et 100
    valSensor = dis(gen);
    return valSensor;
}

bool lightSensor::aleaSensorValue() { // Fonction qui génère une valeur aléatoire de type bool pour le capteur lumière
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1); // On génère un nombre aléatoire entre 0 et 1
    valSensor = dis(gen);
    return valSensor;
}

/**********************************************************/

void scheduler::run() { // Fonction qui lance le programme
    string answer;
    Server server;
    cout << "Do you want the consol writing? (Y/N)" << endl; // On demande à l'utilisateur s'il veut l'affichage dans la console
    cin >> answer;
    verifYesNo(answer); // On vérifie que l'utilisateur a bien répondu par Y ou N
    if (answer[0] == 'Y' || answer[0] == 'y') {
        server.consolActivation = true; // Si l'utilisateur a répondu Y, on active l'affichage dans la console
    }
    cout << "Do you want the log writing? (Y/N)" << endl; // On demande à l'utilisateur s'il veut l'affichage dans le fichier log
    cin >> answer;
    verifYesNo(answer); // On vérifie que l'utilisateur a bien répondu par Y ou N
    if (answer[0] == 'Y' || answer[0] == 'y') {
        server.logActivation = true; // Si l'utilisateur a répondu Y, on active l'affichage dans le fichier log
    }
    cout<<"Do you want a sound sensor? (Y/N)"<<endl; // On demande à l'utilisateur s'il veut un capteur son
    cin >> answer;
    verifYesNo(answer); // On vérifie que l'utilisateur a bien répondu par Y ou N
    if (answer[0] == 'Y' || answer[0] == 'y') {
        server.soundSensor = true; // Si l'utilisateur a répondu Y, on active le capteur son
        cout <<"How often do you want to read the sound sensor? (in seconds)" << endl; // On demande à l'utilisateur la fréquence de lecture du capteur son
        cin >> answer;
        server.intervalSound=verifnumber(answer); // On vérifie que l'utilisateur a bien répondu par un nombre
    }
    cout<<"Do you want a temperature sensor? (Y/N)"<<endl; // On demande à l'utilisateur s'il veut un capteur température
    cin >> answer;
    verifYesNo(answer); // On vérifie que l'utilisateur a bien répondu par Y ou N
    if (answer[0] == 'Y' || answer[0] == 'y') {
        server.temperatureSensor = true; // Si l'utilisateur a répondu Y, on active le capteur température
        cout <<"How often do you want to read the temperature sensor? (in seconds)" << endl; // On demande à l'utilisateur la fréquence de lecture du capteur température
        cin >> answer;
        server.intervalTemperature=verifnumber(answer); // On vérifie que l'utilisateur a bien répondu par un nombre
    }
    cout<<"Do you want a light sensor? (Y/N)"<<endl; // On demande à l'utilisateur s'il veut un capteur lumière
    cin >> answer;
    verifYesNo(answer); // On vérifie que l'utilisateur a bien répondu par Y ou N
    if (answer[0] == 'Y' || answer[0] == 'y') {
        server.lightSensor = true; // Si l'utilisateur a répondu Y, on active le capteur lumière
        cout <<"How often do you want to read the light sensor? (in seconds)" << endl; // On demande à l'utilisateur la fréquence de lecture du capteur lumière
        cin >> answer;
        server.intervalLight=verifnumber(answer); // On vérifie que l'utilisateur a bien répondu par un nombre
    }
    cout<<"Do you want a humidity sensor? (Y/N)"<<endl; // On demande à l'utilisateur s'il veut un capteur humidité
    cin >> answer;
    verifYesNo(answer); // On vérifie que l'utilisateur a bien répondu par Y ou N
    if (answer[0] == 'Y' || answer[0] == 'y') {
        server.humiditySensor = true; // Si l'utilisateur a répondu Y, on active le capteur humidité
        cout <<"How often do you want to read the humidity sensor? (in seconds)" << endl; // On demande à l'utilisateur la fréquence de lecture du capteur humidité
        cin >> answer;
        server.intervalHumidity=verifnumber(answer); // On vérifie que l'utilisateur a bien répondu par un nombre
    }
    // On lance les threads
    thread t1(&scheduler::son, this, ref(server));
    thread t2(&scheduler::temperature, this, ref(server));
    thread t3(&scheduler::lumiere, this, ref(server));
    thread t4(&scheduler::humidite, this, ref(server));
    thread t5(&scheduler::entre, this, ref(server));
    // On attend que les threads se terminent
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}

void scheduler::son(Server &server) { // Fonction qui lance le thread du capteur son
    soundSensor S;
    while (true) { // On lance une boucle infinie car l'utilisateur peut choisir de désactiver ou d'activer le capteur
        if (server.soundSensor) { // Si le capteur son est activé
            this_thread::sleep_for(server.intervalSound * 1000ms); // On attend le temps défini par l'utilisateur
            server.sound = S.aleaSensorValue(); // On récupère la valeur du capteur son
            server.printvalue("sound"); // On affiche la valeur du capteur son

        }
    }
}

void scheduler::temperature(Server &server) { // Fonction qui lance le thread du capteur température
    temperatureSensor T;
    while (true) { // On lance une boucle infinie car l'utilisateur peut choisir de désactiver ou d'activer le capteur
        if (server.temperatureSensor) { // Si le capteur température est activé
            this_thread::sleep_for(server.intervalTemperature * 1000ms); // On attend le temps défini par l'utilisateur
            server.temperature = T.aleaSensorValue(); // On récupère la valeur du capteur température
            server.printvalue("temperature"); // On affiche la valeur du capteur température

        }
    }
}

void scheduler::lumiere(Server & server) { // Fonction qui lance le thread du capteur lumière
    lightSensor L;
    while (true) { // On lance une boucle infinie car l'utilisateur peut choisir de désactiver ou d'activer le capteur
        if (server.lightSensor) { // Si le capteur lumière est activé
            this_thread::sleep_for(server.intervalLight * 1000ms); // On attend le temps défini par l'utilisateur
            server.light = L.aleaSensorValue(); // On récupère la valeur du capteur lumière
            server.printvalue("light"); // On affiche la valeur du capteur lumière
        }
    }
}

void scheduler::humidite(Server &server) { // Fonction qui lance le thread du capteur humidité
    humiditySensor H;
    while (true) { // On lance une boucle infinie car l'utilisateur peut choisir de désactiver ou d'activer le capteur
        if (server.humiditySensor) { // Si le capteur humidité est activé
            this_thread::sleep_for(server.intervalHumidity * 1000ms); // On attend le temps défini par l'utilisateur
            server.humidity = H.aleaSensorValue(); // On récupère la valeur du capteur humidité
            server.printvalue("humidity"); // On affiche la valeur du capteur humidité
        }
    }
}

void scheduler::entre(Server &server) { // Fonction qui lance le thread de l'entrée utilisateur
    string rep;
    string answer;
    while (true) { // On lance une boucle infinie car l'utilisateur peut rentrer une commande à tout moment

        bool temp1 = false, temp2 = false,son=false,light=false,humidity=false,temperature=false; // On initialise des booléens qui nous permettront de savoir si les capteurs sont activés ou non
        fflush(stdin);
        cin >> rep; // On récupère la commande de l'utilisateur
        if (rep.size()==1){
            if (rep[0] == 'q' || rep[0] == 'Q') {
                cout << "End of program" << endl; // Si l'utilisateur répond Q, on quitte le programme
                exit(0);
            } else if (rep[0] == 'l' || rep[0] == 'L') { // Si l'utilisateur répond L
                if (server.logActivation) { // Si le log est activé, on désactive le log
                    cout << "Log desactivation" << endl;
                    server.logActivation = false;
                } else { // Sinon on l'active
                    cout << "Log activation" << endl;
                    server.logActivation = true;
                }
            } else if (rep[0] == 'c' || rep[0] == 'C') { // Si l'utilisateur répond C
                if (server.consolActivation) { // Si la console est activée, on la désactive
                    cout << "Consol desactivation" << endl;
                    server.consolActivation = false;
                } else { // Sinon on l'active
                    cout << "Consol activation" << endl;
                    server.consolActivation = true;
                }
            }
            if (rep[0] == 's' || rep[0] == 'S') { // Si l'utilisateur répond S
                if (server.soundSensor) { // Si le capteur son est activé, on le désactive
                    cout << "Sound sensor desactivation" << endl;
                    server.soundSensor = false;
                } else { // Sinon on l'active
                    // On sauvegarde les valeurs des autres capteurs et des sorties
                    temp1=server.consolActivation;
                    temp2=server.logActivation;
                    server.consolActivation = false;
                    server.logActivation = false;
                    light=server.lightSensor;
                    humidity=server.humiditySensor;
                    temperature=server.temperatureSensor;
                    server.lightSensor=false;
                    server.humiditySensor=false;
                    server.temperatureSensor=false;
                    cout << "Sound sensor activation" << endl;
                    cout <<"How often do you want to read the sound sensor? (in seconds)" << endl;
                    cin >> answer; // On récupère le temps d'attente entre chaque lecture du capteur son
                    server.intervalSound=verifnumber(answer); // On vérifie que le temps d'attente est bien un nombre
                    // On réactive les capteurs et les sorties
                    server.soundSensor = true;
                    server.lightSensor=light;
                    server.humiditySensor=humidity;
                    server.temperatureSensor=temperature;
                    server.consolActivation = temp1;
                    server.logActivation = temp2;
                }
            } else if (rep[0] == 't' || rep[0] == 'T') { // Si l'utilisateur répond T
                if (server.temperatureSensor) { // Si le capteur température est activé, on le désactive
                    cout << "Temperature sensor desactivation" << endl;
                    server.temperatureSensor = false;
                } else { // Sinon on l'active
                    // On sauvegarde les valeurs des autres capteurs et des sorties
                    temp1=server.consolActivation;
                    temp2=server.logActivation;
                    son=server.soundSensor;
                    light=server.lightSensor;
                    humidity=server.humiditySensor;
                    server.soundSensor=false;
                    server.lightSensor=false;
                    server.humiditySensor=false;
                    server.consolActivation = false;
                    server.logActivation = false;
                    cout << "Temperature sensor activation" << endl;
                    cout <<"How often do you want to read the temperature sensor? (in seconds)" << endl;
                    cin >> answer; // On récupère le temps d'attente entre chaque lecture du capteur température
                    server.intervalTemperature=verifnumber(answer); // On vérifie que le temps d'attente est bien un nombre
                    // On réactive les capteurs et les sorties
                    server.temperatureSensor = true;
                    server.soundSensor=son;
                    server.lightSensor=light;
                    server.humiditySensor=humidity;
                    server.consolActivation = temp1;
                    server.logActivation = temp2;
                }
            } else if (rep[0] == 'h' || rep[0] == 'H') { // Si l'utilisateur répond H
                if (server.humiditySensor) { // Si le capteur humidité est activé, on le désactive
                    cout << "Humidity sensor desactivation" << endl;
                    server.humiditySensor = false;
                } else { // Sinon on l'active
                    // On sauvegarde les valeurs des autres capteurs et des sorties
                    temp1=server.consolActivation;
                    temp2=server.logActivation;
                    son=server.soundSensor;
                    light=server.lightSensor;
                    temperature=server.temperatureSensor;
                    server.soundSensor=false;
                    server.lightSensor=false;
                    server.temperatureSensor=false;
                    server.consolActivation = false;
                    server.logActivation = false;
                    cout << "Humidity sensor activation" << endl;
                    cout <<"How often do you want to read the humidity sensor? (in seconds)" << endl;
                    cin >> answer; // On récupère le temps d'attente entre chaque lecture du capteur humidité
                    server.intervalHumidity=verifnumber(answer); // On vérifie que le temps d'attente est bien un nombre
                    // On réactive les capteurs et les sorties
                    server.humiditySensor = true;
                    server.soundSensor=son;
                    server.lightSensor=light;
                    server.temperatureSensor=temperature;
                    server.consolActivation = temp1;
                    server.logActivation = temp2;
                }
            } else if (rep[0] == 'i' || rep[0] == 'I') { // Si l'utilisateur répond I
                if (server.lightSensor) { // Si le capteur lumière est activé, on le désactive
                    cout << "Light sensor desactivation" << endl;
                    server.lightSensor = false;
                } else { // Sinon on l'active
                    // On sauvegarde les valeurs des autres capteurs et des sorties
                    temp1=server.consolActivation;
                    temp2=server.logActivation;
                    son=server.soundSensor;
                    humidity=server.humiditySensor;
                    temperature=server.temperatureSensor;
                    server.soundSensor=false;
                    server.humiditySensor=false;
                    server.temperatureSensor=false;
                    server.consolActivation = false;
                    server.logActivation = false;
                    cout << "Light sensor activation" << endl;
                    cout <<"How often do you want to read the light sensor? (in seconds)" << endl;
                    cin >> answer; // On récupère le temps d'attente entre chaque lecture du capteur lumière
                    server.intervalLight=verifnumber(answer); // On vérifie que le temps d'attente est bien un nombre
                    // On réactive les capteurs et les sorties
                    server.lightSensor = true;
                    server.soundSensor=son;
                    server.humiditySensor=humidity;
                    server.temperatureSensor=temperature;
                    server.consolActivation = temp1;
                    server.logActivation = temp2;
                }
            }
            if (!server.soundSensor && !server.temperatureSensor && !server.humiditySensor && !server.lightSensor) {
                cout << "No sensor activated" << endl; // Si aucun capteur n'est activé, on quitte de programme
                exit(0);

            }
            if (!server.consolActivation && !server.logActivation) { // Si aucune sortie n'est activée
                cout << "No output activated" << endl;
                cout << "Do you want to quit ?(Y/N)" << endl; // On demande à l'utilisateur s'il veut quitter le programme
                cin >> rep;
                verifYesNo(rep); // On vérifie que l'utilisateur a bien répondu par Y ou N
                if (rep[0] == 'y' || rep[0] == 'Y') {
                    cout << "End of program" << endl; // Si l'utilisateur répond Y, on quitte le programme
                    exit(0);
                }
            }
        }
    }
}

/**********************************************************/

Server::Server(const Server &S){ // Constructeur de copie
    consolActivation=S.consolActivation;
    logActivation=S.logActivation;
    sound=S.sound;
    temperature=S.temperature;
    light=S.light;
    humidity=S.humidity;
    soundSensor=S.soundSensor;
    temperatureSensor=S.temperatureSensor;
    lightSensor=S.lightSensor;
    humiditySensor=S.humiditySensor;
    intervalSound=S.intervalSound;
    intervalTemperature=S.intervalTemperature;
    intervalLight=S.intervalLight;
    intervalHumidity=S.intervalHumidity;
}

Server &Server::operator=(const Server &S){ // Opérateur d'affectation
    if(this!=&S){
        this->consolActivation=S.consolActivation;
        this->logActivation=S.logActivation;
        this->sound=S.sound;
        this->temperature=S.temperature;
        this->light=S.light;
        this->humidity=S.humidity;
        this->soundSensor=S.soundSensor;
        this->temperatureSensor=S.temperatureSensor;
        this->lightSensor=S.lightSensor;
        this->humiditySensor=S.humiditySensor;
        this->intervalSound=S.intervalSound;
        this->intervalTemperature=S.intervalTemperature;
        this->intervalLight=S.intervalLight;
        this->intervalHumidity=S.intervalHumidity;
    }
    return (*this);
}

template<class T>
void Server::fileWrite(string name_, T value) const{ // Ecriture dans un fichier
    if (logActivation){ // Si l'écriture dans un fichier est activée
        ofstream file; // On ouvre le fichier en mode écriture à la fin du fichier
        file.open(name_, ios::app | ios::ate);
        if (!file.is_open()) { // Si le fichier n'est pas ouvert, on affiche un message d'erreur
            cout << "Error opening file" << endl;
            exit(1);
        }
        file << value << endl; // On écrit la valeur dans le fichier
        file.close(); // On ferme le fichier
    }
}

void Server::consolWrite(const string& name) const{ // Ecriture dans la console
    if (soundSensor){ // Si le capteur son est activé
        if (name == "sound"){ // Si le nom du capteur est sound
            cout << "Last Sound capted: " << sound <<" dB"<< endl; // Si le capteur son est activé et si le nom du capteur est sound, on affiche la dernière valeur captée par le capteur son
        }
    }
    if (temperatureSensor){
        if (name == "temperature"){
            cout << "Last Temperature capted: " << temperature <<" C"<< endl; // Si le capteur température est activé et si le nom du capteur est temperature, on affiche la dernière valeur captée par le capteur température
        }
    }
    if (lightSensor){
        if (name == "light"){ // Si le capteur lumière est activé et si le nom du capteur est light, on affiche la dernière valeur captée par le capteur lumière
            if (light){
                cout << "Last Light capted: ON" << endl;
            } else {
                cout << "Last Light capted: OFF" << endl;
            }
        }
    }
    if (humiditySensor){
        if (name == "humidity"){
            cout << "Last Humidity capted: " << humidity <<"%"<< endl; // Si le capteur humidité est activé et si le nom du capteur est humidity, on affiche la dernière valeur captée par le capteur humidité
        }
    }
}

Server &Server::operator<<(const Server &S) { // Opérateur de flux
    if (S.consolActivation){ // Si l'écriture dans la console est activée
        S.consolWrite(); // On écrit dans la console
    }
    if (S.logActivation){
        if (S.soundSensor){
            S.fileWrite("sound.txt", S.sound); //Si le capteur son est activé, on écrit dans le fichier sound.txt
        }
        if (S.temperatureSensor){
            S.fileWrite("temperature.txt", S.temperature); //Si le capteur température est activé, on écrit dans le fichier temperature.txt
        }
        if (S.humiditySensor){
            S.fileWrite("humidity.txt", S.humidity); //Si le capteur humidité est activé, on écrit dans le fichier humidity.txt
        }
        if (S.lightSensor){
            if (S.light){ //Si le capteur lumière est activé, on écrit dans le fichier light.txt
                S.fileWrite("light.txt", "ON");
            } else {
                S.fileWrite("light.txt", "OFF");
            }
        }
    }
    return (*this);
}

void Server::printvalue(const string& name) const { // Affichage de la dernière valeur captée par un capteur
    if (this->consolActivation){ // Si l'écriture dans la console est activée
        this->consolWrite(name); // On écrit dans la console
    }
    if (this->logActivation){
        if (soundSensor){
            if (name == "sound"){
                this->fileWrite("sound.txt", this->sound); //Si le capteur son est activé et si le nom du capteur est sound, on écrit dans le fichier sound.txt
            }
        }
        if (temperatureSensor){
            if (name == "temperature"){
                this->fileWrite("temperature.txt", this->temperature); //Si le capteur température est activé et si le nom du capteur est temperature, on écrit dans le fichier temperature.txt
            }
        }
        if (humiditySensor){
            if (name == "humidity"){
                this->fileWrite("humidity.txt", this->humidity); //Si le capteur humidité est activé et si le nom du capteur est humidity, on écrit dans le fichier humidity.txt
            }
        }
        if (lightSensor){
            if (name == "light"){
                if (this->light){ //Si le capteur lumière est activé et si le nom du capteur est light, on écrit dans le fichier light.txt
                    this->fileWrite("light.txt", "ON");
                } else {
                    this->fileWrite("light.txt", "OFF");
                }
            }
        }
    }
}

void Server::consolWrite() const { // Ecriture dans la console
    if (soundSensor){ // Si le capteur son est activé
        cout << "Last Sound capted: " << sound <<" dB"<< endl;
    }
    if (temperatureSensor){ // Si le capteur température est activé
        cout << "Last Temperature capted: " << temperature <<" C"<< endl;
    }
    if (lightSensor){ // Si le capteur lumière est activé
        if (light){
            cout << "Last Light capted: ON" << endl;
        } else {
            cout << "Last Light capted: OFF" << endl;
        }
    }
    if (humiditySensor){ // Si le capteur humidité est activé
        cout << "Last Humidity capted: " << humidity <<"%"<< endl;
    }
}




