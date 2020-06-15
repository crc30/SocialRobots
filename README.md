# Documentazione Controller Tiago Titanium


## Installazione


1. Download webots
2. Download project from github
3. Open webots
4. Click File > Open Scenario
5. Select .wbt in /worlds/tiago_world_dale_castiglione.wbt

### Come aggiungere un segno


Il codice suddivide ogni parte del corpo in piccoli array di diverse dimensioni.
Se i valori del movimento che vorresti far eseguire non sono presenti nella lista degli array presenti nel codice puoi aggiungerli creando degli array specifici per ogni parte del corpo nel seguente modo:

* double my_head_torso[3] = {0.00, 0.00, 0.00};
* double my_arm[4] = {0.00, 0.00, 0.00, 0.00};
* double my_hand[3] = {0.00, 0.00, 0.00};
* double my_thumb[5] = {0.00, 0.00, 0.00, 0.00, 0.00};
* double my_index[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
* double my_middle[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
* double my_ring[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
* double my_little[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
* double my_wheel[2] = {0.00, 0.00};

Successivamente puoi creare la funzione per far eseguire il tuo segno.
La tua funzione personalizzata chiamerà la funzione principale
**static void setTiagoPositionCompos( char \*my_names[], int time_step, double interval, double \*arm, double \*palm, double \*thumb, double \*index, double \*middle, double \*ring, double \*little );**

* \*my_names[] contiene i nomi di tutti i motori presenti nel robot (non serve modificarla, è già mappata)
* double interval è il valore che indica per quanto tempo deve essere esiguito il segno
* le altre variabili sono array di valori dichiarati precedentemente.

Supponiamo che tu voglia creare una funzione che permette al robot di eseguire il segno della birra:

Dopo aver dichiarato gli array, come specificato sopra, bisogna creare una funzione nel modo seguente:

**static void beer(char *names[], int time_step) {\
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;setTiagoPositionCompos(names, time_step, 0.00, my_arm, my_hand, my_thumb, my_index, my_middle, my_ring, my_little);\
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;setTiagoPositionCompos(names, time_step, 4.00, my_arm_1, my_hand_1, my_thumb_1, my_index_1, my_middle_1, my_ring_1, my_little_1);\
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;setTiagoPositionCompos(names, time_step, 2.00, my_arm_2, my_hand_2, my_thumb_2, my_index_2, my_middle_2, my_ring_2, my_little_2);\
}**

Come possiamo vedere dal codice appena descritto la nostra funzione **beer** richiama la **setTiagoPositionCompos** con i valori degli array precedentemente dichiarati e il valore time (**0.00, 4.00, 2.00**) indicano che quei il motore del robot deve mantenere la posizione per quella durata prima di eseguire l'altra funzione. L'array **\*my_names[]** non deve essere mai modificato in quanto è già inizializzato con tutti i nomi dei motori del robot, il nostro compito è semplicemente associare i valori per ogni motore attraverso gli array **my_arm, my_hand**, etc..
L'intero **int time_step** che richiamiamo in ogni funzione è inizializzato nel **main** e ritorna  returns the value of the basicTimeStep field of the WorldInfo node. The basicTimeStep field defines the duration of the simulation step executed by Webots.

L'esecuzione delle funzioni è gestita tramite rilevamento input da tastiera e intercettato tramite uno switch case nel main.

# Documentazione

Function setTiagoPositionCompos
======================

La setTiagoPositionCompos è la funzione principale del nostro codice.
Prende in input l'array my_names[] che contiene i nomi dei motori disponibili nel robot, l'intero time_step returns the value of the basicTimeStep field of the WorldInfo node, l'intero interval che indica per quanto tempo il robot deve eseguire la funzione e il resto degli array che prende in input sono i valori che il robot deve assumere per ogni suo motore, gli unici motori che noi non controlliamo, per il semplice fatto che nel nostro progetto non vengono usati, sono le ruote, la testa e il movimento del busto, per questo motivo questi valori non sono passati alla funzione.

Function main
====

Nella funzione main vengono dichiarate l'array dei motori disponibili del robot, la funzione nativa di webots per abilitare il rilevamento input da tastiera, il time step del robot, si inizializza il robot tramite la funzione wb_robot_init(), infine viene eseguito un while, che rimane attivo per tutta la durata del progetto, in cui è presente un controllo switch case che si occupa di chiamare la funzione relativa all'input inserito dall'utente

Function rotate
======

Questa funzione è di supporto alla setTiagoPositionCompos e si occupa di far ruotare una determinata parte del robot per un certo intervallo di tempo. Questi due valori vengono presi in input dalla funzione e ciò ne consente il riutilizzo.

Function rotate_and_move
===============

Questa funzione è di supporto alla setTiagoPositionCompos e si occupa di far ruotare e muovere contemporaneamente due parti del robot per un certo intervallo di tempo e può essere integrata in qualsiasi altra funzione
