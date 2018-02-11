#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "dungeon1.h"
#include "dungeon2.h"
#include "dungeon3.h"
#include "dungeon4.h"
//#include "weapons.h"




/*
Legend
W = Wall DONE
* = Character DONE
C = Chest (random loot) 
D = Door (closed) DONE
O = Open Chest (open) DONE
  = Open Space DONE
G = Bad Guy
- = Line of Sight
_ = Bed //Saving Locations - Health Restoration
B = Boss
P = Dead Person
E = Exit
T = Tree/Table
L = Lake
*/

bool mapDisplay = true;

typedef struct weapon {
	char* name;
	char* type;
	int damage;
	int value;
	
} weapon;

typedef struct potion {
	char* name;
	int value;
} potion;

typedef struct spells {
	char* name;
	char* type;
	int damage;
} spells;

typedef struct armor {
	char* type;
	int protection;
	char* name;
} armor;

typedef struct character {		// custom class used to layout the charaters formatted stat
	int userMaxHp;	// The maximum health the user can have
    int userCurHp;		// Tthe current health the user can have
  	int userAtk;			// The attack modifyer of the user 
	int userAcc;			// the accuracy modifyer of the user
	int userDef;			// The defence modifyer of the user
	int userSpeed;			// the speed modifyer of the user
	int xp;			// The amount Exy the user currently has
	int lvl;			// The level the user currently is
	weapon userWeapons[2];			// This stores the characters weapons
	spells userSpells[3];			// This stores the characters spells
	potion userPotions[5];			// this stores the characters potions
} character;

typedef struct enemy {
  int defense;
  int health;
  char *weapon1;
  char *weapon2;
  char *weapon3;
  char weakness;
  int fireResist;
  int poiResist;
  int lightResist;
  int slashResist;
  int pierceResist;
  int bludgeResist;
  int weapon1Dam;
  int weapon2Dam;
  int weapon3Dam;
  int lvl;
  int addXP;
  char *name;
} enemy;

void checkLevel();
void generateChar(character mainCar);
void clrscr(void);
void createWeapons(weapon* weaponList);
bool canMove(int* charLoc, int a);
bool loot(int* charLoc, int a, weapon* weaponList, character* mainCar);
bool combatTrigger(int* charLoc, int a, int mapNum, character* mainCar);
bool startCombat(int enemySpeed, character* mainCar);
bool combat (char* enemyAtkChoice, char* enemyName, int enemyAtkDam, int enemyLevel, int enemyHealth, int resistMod, int enemyDefence, int userLevel, int enemySpeed, character* mainCar);
enemy* makeBandit(int userlvl);
enemy* makeBat(int userlvl);
enemy* makeCentar(int userlvl);
enemy* makeCub(int userlvl);
enemy* makeDragon(int userlvl);
enemy* makeKobold(int userlvl);
enemy* makeMimic(int userlvl);
enemy* makeWolves(int userlvl);
enemy* makeGuard(int userlvl);
enemy* makeLizard(int userlvl);

/* void generateChar(character mainCar) { //Fix Character Gen
	mainCar.userMaxHp = 15;
	mainCar.userCurHp = 15;
	mainCar.userAtk = 100;
	mainCar.userDef = 10;
	mainCar.userSpeed = 1;
	mainCar.xp = 0;
	mainCar.lvl = 1;
	mainCar.userWeapons[0].name = "Fists";
	mainCar.userWeapons[0].type = "Blugeoning";
	mainCar.userWeapons[0].damage = 2;
	mainCar.userWeapons[0].value = 0;
	mainCar.userWeapons[1].name = "Fists";
	mainCar.userWeapons[1].type = "Blugeoning";
	mainCar.userWeapons[1].damage = 2;
	mainCar.userWeapons[1].value = 0;
	mainCar.userSpells[0].name = "Fire Ball";
	mainCar.userSpells[0].damage = 3;
	mainCar.userSpells[0].type = "Fire";
	mainCar.userSpells[1].name = "Lightning Bolt";
	mainCar.userSpells[1].damage = 4;
	mainCar.userSpells[1].type = "Electric";
	mainCar.userSpells[2].name = "Poison Cloud";
	mainCar.userSpells[2].damage = 3;
	mainCar.userSpells[2].type = "Poison";
	mainCar.userPotions[0].name = NULL;
	mainCar.userPotions[1].name = NULL;
	mainCar.userPotions[2].name = NULL;
	mainCar.userPotions[3].name = NULL;
	mainCar.userPotions[4].name = NULL;
} */

void clrscr() {
    system("@cls||clear");
}

void createWeapons(weapon* weaponList) {

weaponList[0].name = "Club";
weaponList[0].type = "Bludgeoning";
weaponList[0].damage = 3;
weaponList[0].value = 10;

weaponList[1].name = "Dagger";
weaponList[1].type = "Piercing";
weaponList[1].damage = 3;
weaponList[1].value = 150;

weaponList[2].name = "Spear";
weaponList[2].type = "Piercing";
weaponList[2].damage = 6;
weaponList[2].value = 150;

weaponList[3].name = "Crossbow";
weaponList[3].type = "Piercing";
weaponList[3].damage = 9;
weaponList[3].value = 300;

weaponList[4].name = "Longbow";
weaponList[4].type = "Piercing";
weaponList[4].damage = 6;
weaponList[4].value = 300;

weaponList[5].name = "Greatsword";
weaponList[5].type = "Slashing";
weaponList[5].damage = 8;
weaponList[5].value = 400;

weaponList[6].name = "Pike";
weaponList[6].type = "Piercing";
weaponList[6].damage = 10;
weaponList[6].value = 500;

weaponList[7].name = "Rapier";
weaponList[7].type = "Piercing";
weaponList[7].damage = 7;
weaponList[7].value = 2500;

weaponList[8].name = "Warhammer";
weaponList[8].type = "Bludgeoning";
weaponList[8].damage = 7;
weaponList[8].value = 1500;

weaponList[9].name = "Halberd";
weaponList[9].type = "Slashing";
weaponList[9].damage = 10;
weaponList[9].value = 2000;

};

enemy* makeBat(int userlvl) {
  static enemy bat;
  bat.name = "bat";
  bat.defense = 8;
  bat.lvl = rand()%6 + 10;
  bat.health = (25*bat.lvl)/4;
  bat.weapon1 = "Suck blood";
  bat.weapon2 = "Fly Into Character";
  bat.weapon3 = "Drain health";
  bat.weakness = 'n';
  bat.fireResist = 0;
  bat.poiResist = 0;
  bat.lightResist = 0;
  bat.slashResist = 0;
  bat.pierceResist = 0;
  bat.bludgeResist = 0;  
  bat.weapon1Dam = 7;
  bat.weapon2Dam = 4;
  bat.weapon3Dam = 3;
  bat.addXP = (userlvl*userlvl) * 50 / (21-bat.lvl);
  return &bat;
}

enemy* makeBandit(int userlvl) {
  static enemy bandit;
  bandit.name = "bandit";
  bandit.lvl = 3;
  bandit.defense = 6;
  bandit.health = ((bandit.lvl * 5) + 10)/4;
  bandit.weapon1 = "Punch";
  bandit.weapon2 = "Knife";
  bandit.weapon3 = "Steal health";
  bandit.weakness = 'n';
  bandit.fireResist = 0;
  bandit.poiResist = 0;
  bandit.lightResist = 0;
  bandit.slashResist = 0;
  bandit.pierceResist = 0;
  bandit.bludgeResist = 0;  
  bandit.weapon1Dam = 2;
  bandit.weapon2Dam = 3;
  bandit.weapon3Dam = 5;
  bandit.addXP = (userlvl*userlvl) * 100 / (21-bandit.lvl);
  return &bandit;
}

enemy* makeWolves(int userlvl) {
  static enemy wolves;
  wolves.name = "wolves";
  wolves.defense = 13;
  wolves.lvl = rand()%6 + 10;
  wolves.health = (wolves.lvl * 5)/4;
  wolves.weapon1 = "Bite";
  wolves.weapon2 = "Magic Howl";
  wolves.weapon3 = "Wolf Pack Attack";
  wolves.weakness = 'n';
  wolves.fireResist = 0;
  wolves.poiResist = 0;
  wolves.lightResist = 0;
  wolves.slashResist = 0;
  wolves.pierceResist = 0;
  wolves.bludgeResist = 0;  
  wolves.weapon1Dam = 2;
  wolves.weapon2Dam = 3;
  wolves.weapon3Dam = 5;
  wolves.addXP = (userlvl*userlvl) * 250 / (21-wolves.lvl);
  return &wolves;
}

enemy* makeMimic(int userlvl) {
  static enemy mimic;
  mimic.name = "Wraith";
  mimic.defense = 12;
  mimic.lvl = rand()%6 + 10;
  mimic.health = ((mimic.lvl * 5)+ 18)/4;
  mimic.weapon1 = "Deadly Adhesive";
  mimic.weapon2 = "Life Drain";
  mimic.weapon3 = "Create Spectate";
  mimic.weakness = 'n';
  mimic.fireResist = 0;
  mimic.poiResist = 0;
  mimic.lightResist = 0;
  mimic.slashResist = 0;
  mimic.pierceResist = 0;
  mimic.bludgeResist = 0;  
  mimic.weapon1Dam = 2;
  mimic.weapon2Dam = 3;
  mimic.weapon3Dam = 5;
  mimic.addXP = (userlvl*userlvl) * 500 / (21-mimic.lvl);
  return &mimic;
}

enemy* makeCentaur(int userlvl) {
  static enemy centaur;
  centaur.name = "centaur";
  centaur.defense = 12;
  centaur.lvl = 12;
  centaur.health = ((6 * centaur.lvl) + 12)/4;
  centaur.weapon1 = "Trample With Hooves";
  centaur.weapon2 = "Punch";
  centaur.weapon3 = "Bow and Arrow";
  centaur.weakness = 'n';
  centaur.fireResist = 0;
  centaur.poiResist = 0;
  centaur.lightResist = 0;
  centaur.slashResist = 0;
  centaur.pierceResist = 0;
  centaur.bludgeResist = 0;
  centaur.weapon1Dam = 2;
  centaur.weapon2Dam = 3;
  centaur.weapon3Dam = 5;
  
  centaur.addXP = (userlvl*userlvl) * 125 / (21-centaur.lvl);
  return &centaur;
}

enemy* makeKobold (int userlvl) {
	static enemy kobold;
	kobold.name = "kobold";
 kobold.defense = 12;
 kobold.lvl = rand()%6 + 10;
 kobold.health = (4*kobold.lvl - 3)/4;
 kobold.weapon1 = "Dagger";
 kobold.weapon2 = "Punch";
 kobold.weapon3  = "Trap";
 kobold.weakness = 'n';
 kobold.fireResist = 0;
 kobold.poiResist = 0;
 kobold.lightResist = 0;
 kobold.slashResist = 0;
 kobold.pierceResist = 0;
 kobold.bludgeResist = 0;
 kobold.weapon1Dam = 4;
 kobold.weapon2Dam = 2;
 kobold.weapon3Dam = 8;
 kobold.addXP = (userlvl*userlvl) * 175 / (21-kobold.lvl);
 return &kobold;
  
}

enemy* makeGuard(int userlvl) {
  static enemy guard;
  guard.name = "guard";
  guard.defense = 12;
  guard.health = 10;
  guard.weapon1 = "Punch";
  guard.weapon2 = "Kick";
  guard.weapon3 = "Shortsword";
  guard.weakness = 'n';
  guard.fireResist = 0;
  guard.poiResist = 0;
  guard.lightResist = 0;
  guard.slashResist = 0;
  guard.pierceResist = 0;
  guard.bludgeResist = 0;
  guard.weapon1Dam = 2;
  guard.weapon2Dam = 3;
  guard.weapon3Dam = 5;
  guard.lvl = 1;
  guard.addXP = 75;
  return &guard;
}

enemy* makeTroll(int userlvl) {
  static enemy troll;
  troll.name = "troll";
  troll.defense = 15;
  troll.lvl = 18;
  troll.health = ((6 * troll.lvl) + 40)/4;
  troll.weapon1 = "Scare";
  troll.weapon2 = "Kick";
  troll.weapon3 = "Troll Magic";
  troll.weakness = 'n';
  troll.fireResist = 0;
  troll.poiResist = 0;
  troll.lightResist = 10;
  troll.slashResist = 0;
  troll.pierceResist = 0;
  troll.bludgeResist = 10;
  troll.weapon1Dam = 2;
  troll.weapon2Dam = 3;
  troll.weapon3Dam = 5;
  troll.addXP = (userlvl*userlvl) * 80 / (21-troll.lvl);
  return &troll;
}

enemy* makeLizard(int userlvl) {
    static enemy lizard;
    lizard.name = "lizard";
    lizard.defense = 16;
    lizard.lvl = 18;
    lizard.health = ((20 * lizard.lvl) + 120)/4;
    lizard.weapon1 = "Stomping";
    lizard.weapon2 = "Clawing and Slashing";
    lizard.weapon3 = "Fire";
    lizard.weakness = 'n';
    lizard.fireResist = 100;
    lizard.poiResist = 0;
    lizard.lightResist = 10;
    lizard.slashResist = 10;
    lizard.pierceResist = 10;
    lizard.bludgeResist = 10;
    lizard.weapon1Dam = 2;
    lizard.weapon2Dam = 3;
    lizard.weapon3Dam = 5;
    lizard.addXP = (userlvl*userlvl)*100/(21-lizard.lvl);
    return &lizard;
}

enemy* makeCube(int userlvl) {
  static enemy cube;
  cube.name = "cube";
  cube.defense = 6;
  cube.lvl = 3;
  cube.health = ((6 * 3) + 40)/4;
  cube.weapon1 = "Oozing matter";
  cube.weapon2 = "Paralyze and Trip";
  cube.weapon3 = "Pounce and Devour";
  cube.weakness = 'n';
  cube.fireResist = -30;
  cube.poiResist = 0;
  cube.lightResist = 10;
  cube.slashResist = 0;
  cube.pierceResist = 0;
  cube.bludgeResist = 10;
  cube.weapon1Dam = 2;
  cube.weapon2Dam = 3;
  cube.weapon3Dam = 5;
  cube.addXP = (userlvl*userlvl) * 4000 / (21-cube.lvl);
  return &cube;
}

enemy* makeDragon(int userlvl) {
    static enemy dragon;
    dragon.name = "dragon";
    dragon.defense = 19;
	dragon.lvl = 20;
    dragon.health = ((20 * dragon.lvl) + 242)/4;
    dragon.weapon1 = "Stomping";
    dragon.weapon2 = "Clawing and Slashing";
    dragon.weapon3 = "Fire";
    dragon.weakness = 'n';
    dragon.fireResist = 100;
    dragon.poiResist = 0;
    dragon.lightResist = 10;
    dragon.slashResist = -10;
    dragon.pierceResist = -10;
    dragon.bludgeResist = -10;
    dragon.weapon1Dam = 2;
    dragon.weapon2Dam = 3;
    dragon.weapon3Dam = 5;
    dragon.addXP = (userlvl*userlvl) * 20000 / (21-dragon.lvl);
    return &dragon;
}
enemy enemySelection (int curMap, int userlvl) {
  	switch (curMap) {
		case 1:
  			return  *makeGuard(userlvl);
  			break;
  		case 2:
  			return *makeBandit(userlvl);
  			break;
  		case 3:
  			if (rand()%2 == 0) {
  				return *makeBat(userlvl);
  			} else {
  				return *makeWolves(userlvl);
  			}
  			break;
  		case 4:
  			if (rand()%2 == 0) {
  				return *makeCentaur(userlvl);
  			} else {
  				return *makeKobold(userlvl);
  			}
  			break;
  		case 5:
  			return *makeLizard(userlvl);
  			break;
  	}
}

bool loot(int* charLoc, int a, weapon* weaponList, character* mainCar) { //May Need to Fix to have Armor & Spells?
	switch (a) {
		char test;
		case 1:
			test = dungeon1[charLoc[0]-1][charLoc[1]];
			if(test == 'C' || test == 'P') {
				clrscr();
				int temp; 
				weapon loot = weaponList[rand()%9];
				loot.damage*= mainCar->lvl;
				printf("You've collected some loot. You found a %s. It has a damage of %d.\n",loot.name,loot.damage);
				printf("Your current weapons are a %s with a damage of %d and a %s with a damage of %d.",mainCar->userWeapons[0].name,mainCar->userWeapons[0].damage,mainCar->userWeapons[1].name,mainCar->userWeapons[1].damage);
				printf("\nIf you would like to change a weapon you have please enter the slot number. Enter a 0 to discard the looted weapon. Input: ");
				scanf("%d",&temp);
				if(temp == 1) {
					mainCar->userWeapons[0] = loot;
				} else if (temp == 2) {
					mainCar->userWeapons[1] = loot;
				}
				dungeon1[charLoc[0]-1][charLoc[1]] = 'U';
				return false;
			} else {
				return true;
			}
			break;
		case 2:
			test = dungeon1[charLoc[0]][charLoc[1]-1];
			if(test == 'C' || test == 'P') {
				clrscr();
				int temp; 
				weapon loot = weaponList[rand()%9];
				loot.damage*= mainCar->lvl;
				printf("You've collected some loot. You found a %s. It has a damage of %d.\n",loot.name,loot.damage);
				printf("Your current weapons are a %s with a damage of %d and a %s with a damage of %d.",mainCar->userWeapons[0].name,mainCar->userWeapons[0].damage,mainCar->userWeapons[1].name,mainCar->userWeapons[1].damage);
				printf("\nIf you would like to change a weapon you have please enter the slot number. Enter a 0 to discard the looted weapon. Input: ");
				scanf("%d",&temp);
				if(temp == 1) {
					mainCar->userWeapons[0] = loot;
				} else if (temp == 2) {
					mainCar->userWeapons[1] = loot;
				}
				dungeon1[charLoc[0]][charLoc[1]-1] = 'U';
				return false;
			} else {
				return true;
			}
			
			break;
		case 3:
			test = dungeon1[charLoc[0]+1][charLoc[1]];
			if(test == 'C' || test == 'P') {
				clrscr();
				int temp; 
				weapon loot = weaponList[rand()%9];
				loot.damage*= mainCar->lvl;
				printf("You've collected some loot. You found a %s. It has a damage of %d.\n",loot.name,loot.damage);
				printf("Your current weapons are a %s with a damage of %d and a %s with a damage of %d.",mainCar->userWeapons[0].name,mainCar->userWeapons[0].damage,mainCar->userWeapons[1].name,mainCar->userWeapons[1].damage);
				printf("\nIf you would like to change a weapon you have please enter the slot number. Enter a 0 to discard the looted weapon. Input: ");
				scanf("%d",&temp);
				if(temp == 1) {
					mainCar->userWeapons[0] = loot;
				} else if (temp == 2) {
					mainCar->userWeapons[1] = loot;
				}
				dungeon1[charLoc[0]+1][charLoc[1]] = 'U';
				return false;
			} else {
				return true;
			}
			
			break;
		case 4:
			test = dungeon1[charLoc[0]][charLoc[1]+1];
			if(test == 'C' || test == 'P') {
				clrscr();
				int temp; 
				weapon loot = weaponList[rand()%9];
				loot.damage*= mainCar->lvl; 
				printf("You've collected some loot. You found a %s. It has a damage of %d.\n",loot.name,loot.damage);
				printf("Your current weapons are a %s with a damage of %d and a %s with a damage of %d.",mainCar->userWeapons[0].name,mainCar->userWeapons[0].damage,mainCar->userWeapons[1].name,mainCar->userWeapons[1].damage);
				printf("\nIf you would like to change a weapon you have please enter the slot number. Enter a 0 to discard the looted weapon. Input: ");
				scanf("%d",&temp);
				if(temp == 1) {
					mainCar->userWeapons[0] = loot;
				} else if (temp == 2) {
					mainCar->userWeapons[1] = loot;
				}
				dungeon1[charLoc[0]][charLoc[1]+1] = 'U';
				return false;
			} else {
				return true;
			}
			break;
			
		default:
			return false;
			break;
			
	}
}

bool canMove(int* charLoc, int a) {
	switch(a){
		char test;
		case 1:
			test = dungeon1[charLoc[0]-1][charLoc[1]];
			if(test == 'W' || test == 'C' || test == 'G' || test == 'B' || test == 'P' || test == '-' || test == '+' || test == 'T') {
				return false;
			} else {
				return true;
			}
			break;
		case 2:
			test = dungeon1[charLoc[0]][charLoc[1]-1];
			if(test == 'W' || test == 'C' || test == 'G' || test == 'B' || test == 'P' || test == '-' || test == '+' || test == 'T') {
				return false;
			} else {
				return true;
			}
			break;
		case 3:
			test = dungeon1[charLoc[0]+1][charLoc[1]];
			if(test == 'W' || test == 'C' || test == 'G' || test == 'B' || test == 'P' || test == '-' || test == '+' || test == 'T') {
				return false;
			} else {
				return true;
			}
			break;
		case 4:
			test = dungeon1[charLoc[0]][charLoc[1]+1];
			if(test == 'W' || test == 'C' || test == 'G' || test == 'B' || test == 'P' || test == '-' || test == '+' || test == 'T') {
				return false;
			} else {
				return true;
			}
			break;

		default:
			return false;

	}

}


bool startCombat (int enemySpeed, character* mainCar) {
//	int enemySpeed 		= enemySpeed;	//pointer subject to change	// This gets the current enemy's speed and stores it
	int userInitiative	=	rand()%19 + mainCar->userSpeed;	// This calculates the users inititive
	int enemyinitiative	=	rand()%19 + enemySpeed;	// This calculates the enemys initiative
	
	bool userTurn;									// This stores whos turn it is
	
	if (userInitiative > enemyinitiative) {			// This check to see if the user goes first
		userTurn = true;							// Tell the program the user goes first
	} else if (userInitiative < enemyinitiative) {		// This checks to see if the enemy goes first
		userTurn = false;							// tell the program the enemy goes first
	} else {										// to see if the initiatives of the two are equil
		if (mainCar->userSpeed > enemySpeed) {		// This checks to see if the user is faster
			userTurn = true;						// Tell the program the user goes first
		} else {									// This checks to see of the enemy is faster
			userTurn = false;						// Tells the program the user is faster
		}
	}
	return userTurn;
}

bool combat (char* enemyAtkChoice, char* enemyName, int enemyAtkDam, int enemyLevel, int enemyHealth, int resistMod, int enemyDefence, int userLevel, int enemySpeed, character* mainCar) {
	bool userTurn = startCombat(enemySpeed, mainCar);						// function used to undergo combat
	do {
		if (userTurn) {														// Checks to see whos turn it is
			printf("What attack would you like to do? ");
			printf("[1]%s, ", mainCar->userWeapons[0].name);	
			printf("[2]%s, ", mainCar->userWeapons[1].name);
			printf("[3]%s, ", mainCar->userSpells[0].name);
			printf("[4]%s, ", mainCar->userSpells[1].name);
			printf("[5]%s, ", mainCar->userSpells[2].name);
			printf("[6]Health Potion. Choice: ");
			int atkChoice = 0, atkDamage = 0;
			char *atkName;
			bool atkTrue = true;
			scanf("%d", &atkChoice);
			switch(atkChoice) {
				case 1:
					atkDamage = mainCar->userWeapons[0].damage;
					atkName = mainCar->userWeapons[0].name;
					break;
				case 2:
					atkDamage = mainCar->userWeapons[1].damage;
					atkName = mainCar->userWeapons[1].name;
					break;
				case 3:
					atkDamage = mainCar->userSpells[0].damage;
					atkName = mainCar->userSpells[0].name;
					break;
				case 4:
					atkDamage = mainCar->userSpells[1].damage;
					atkName = mainCar->userSpells[1].name;
					break;
				case 5:
					atkDamage = mainCar->userSpells[2].damage;
					atkName = mainCar->userSpells[2].name;
					break;
				case 6:
					atkDamage = mainCar->userPotions[0].value;
					atkTrue = false;
					break;
				default:
					atkDamage = mainCar->userWeapons[0].damage;
					atkName = mainCar->userWeapons[0].name;
					break;
					
			}
			if(atkTrue) {
			
				if(rand()%19+1+(mainCar->lvl/2) <= enemyDefence) {
					enemyHealth -= atkDamage;
					printf("You attack with your %s dealing %d damage to the %s.\n", atkName,atkDamage,enemyName);
				} else {
					printf("You attack with your %s but you miss the %s.\n",atkName,enemyName);
				}
			} else {
				printf("You healed yourself for %d points.\n", atkDamage);
				mainCar->userCurHp += atkDamage;
				if(mainCar->userCurHp > mainCar->userMaxHp) { 
					mainCar->userCurHp = mainCar->userMaxHp;
				}
				atkTrue = true;
			}
			
			
			userTurn = false;
		} else {
			if ( enemyLevel/2+(rand()%19+1) < mainCar->userDef) {
				userTurn = true;
				printf("The %s missed you.\n",enemyName);
			} else {
				mainCar->userCurHp -= enemyAtkDam;
				printf("The %s used %s dealing %d points of damage.\n", enemyName, enemyAtkChoice, enemyAtkDam);
				userTurn = true;
			}
		}
	} while (mainCar->userCurHp > 0 && enemyHealth > 0);
	
	if (mainCar->userCurHp > 0) {
		printf("Congratz you didn't die! Beat my exspectations. =)\n");
		
		return true;
	} else {
		printf("Well, you done fucked up.\n");
		return false;
	}
}

int* clearBoard(int loc[]) {
	if (dungeon1[loc[0]][loc[1]] == '-' || dungeon1[loc[0]][loc[1]] == '+' ) {
		dungeon1[loc[0]][loc[1]] = ' ';
		int tempArray[2] = {loc[0]-1, loc[1]};
		clearBoard(tempArray);
		tempArray[0] = loc[0];
		tempArray[1] = loc[1]-1;
		clearBoard(tempArray);
		tempArray[0] = loc[0]+1;
		tempArray[1] = loc[1];
		clearBoard(tempArray);
		tempArray[0] = loc[0];
		tempArray[1] = loc[1]+1;
		clearBoard(tempArray);
	} else if (dungeon1[loc[0]][loc[1]] == 'B' || dungeon1[loc[0]][loc[1]] == 'G' ) { 
		dungeon1[loc[0]][loc[1]] = 'P';
	} else {
		return '\0';
	}
				
}

bool combatTrigger(int* charLoc, int a, int mapNum, character* mainCar) {
	switch(a) {
		char test;
		bool win = false;
		case 1:
			test = dungeon1[charLoc[0]-1][charLoc[1]];
			if(test == '-' || test == 'G') {
				enemy temp = enemySelection(mapNum, mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0]-1,charLoc[1]};
					mainCar->xp += temp.addXP;
					clearBoard(tempA);
				} else {
					mapDisplay = false;
				}
				return false;
			} else if (test == '+' || test == 'B'){
				enemy temp = *makeCube(mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0]-1,charLoc[1]};
					clearBoard(tempA);
					mainCar->xp += temp.addXP;
				} else {
					mapDisplay = false;
				}
			} else {
				return true;
			}
			break;
		case 2:
			test = dungeon1[charLoc[0]][charLoc[1]-1];
			if(test == '-' || test == 'G') {
				enemy temp = enemySelection(mapNum, mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0],charLoc[1]-1};
					clearBoard(tempA);
					mainCar->xp += temp.addXP;
				} else {
					mapDisplay = false;
				}
				return false;
			} else if (test == '+' || test == 'B'){
				enemy temp = *makeCube(mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0],charLoc[1]-1};
					clearBoard(tempA);
					mainCar->xp += temp.addXP;
				} else {
					mapDisplay = false;
				}
			} else {
				return true;
			}
			break;
		case 3:
			test = dungeon1[charLoc[0]+1][charLoc[1]];
			if(test == '-' || test == 'G') {
				enemy temp = enemySelection(mapNum, mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0]+1,charLoc[1]};
					clearBoard(tempA);
					mainCar->xp += temp.addXP;
				} else {
					mapDisplay = false;
				}
				return false;
			} else if (test == '+' || test == 'B'){
				enemy temp = *makeCube(mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0]+1,charLoc[1]};
					clearBoard(tempA);
					mainCar->xp += temp.addXP;
				} else {
					mapDisplay = false;
				}
			} else {
				return true;
			}
			break;
		case 4:
			test = dungeon1[charLoc[0]][charLoc[1]+1];
			if(test == '-' || test == 'G') {
				enemy temp = enemySelection(mapNum, mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0],charLoc[1]+1};
					clearBoard(tempA);
					mainCar->xp += temp.addXP;
				} else {
					mapDisplay = false;
				}
				return false;
			} else if (test == '+' || test == 'B'){
				enemy temp = *makeCube(mainCar->lvl);
				int x = rand()%3;
				switch(x) {
					case 1:
						win = combat(temp.weapon1,temp.name,temp.weapon1Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 2:
						win = combat(temp.weapon2,temp.name,temp.weapon2Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
					case 3:
						win = combat(temp.weapon3,temp.name,temp.weapon3Dam,temp.lvl,temp.health,temp.bludgeResist,temp.defense,mainCar->lvl,rand()%12,mainCar);
						break;
				}
				
				if(win) {
					int tempA[2] = {charLoc[0],charLoc[1]+1};
					clearBoard(tempA);
					mainCar->xp += temp.addXP;
				} else {
					mapDisplay = false;
				}
			} else {
				return true;
			}
			break;
			
		default:
			return false;
			
	}
	return true;
}

void levelUp(character *mainCar) {
	int temp = mainCar->xp%(300+mainCar->lvl*200);
	if(temp > mainCar->lvl) { 
		mainCar->userSpells[0].damage = (mainCar->userSpells[0].damage/mainCar->lvl)*temp;
		mainCar->userSpells[1].damage = (mainCar->userSpells[1].damage/mainCar->lvl)*temp;
		mainCar->userSpells[2].damage = (mainCar->userSpells[2].damage/mainCar->lvl)*temp;
		mainCar->lvl = temp;
		mainCar->userMaxHp += 8;
		mainCar->userCurHp = mainCar->userMaxHp;
	}
}



//Main Function
void main() {	
	bool invalid = false, invalidMove = false, inventoryDisplay = false, healed = false, newMap = false;
	int i, mapNum = 1;
	char input = 'n', lastChar = ' ';
	int charLoc[2] = {23, 3};
	weapon weaponList[10];
	character mainCar;
	time_t result = time(NULL);
	srand((unsigned int)result);
	
	mainCar.userMaxHp = 15;
	mainCar.userCurHp = 15;
	mainCar.userAtk = 100;
	mainCar.userDef = 10;
	mainCar.userSpeed = 1;
	mainCar.xp = 0;
	mainCar.lvl = 1;
	mainCar.userWeapons[0].name = "Fists";
	mainCar.userWeapons[0].type = "Blugeoning";
	mainCar.userWeapons[0].damage = 2;
	mainCar.userWeapons[0].value = 0;
	mainCar.userWeapons[1].name = "Fists";
	mainCar.userWeapons[1].type = "Blugeoning";
	mainCar.userWeapons[1].damage = 2;
	mainCar.userWeapons[1].value = 0;
	mainCar.userSpells[0].name = "Fire Ball";
	mainCar.userSpells[0].damage = 100;
	mainCar.userSpells[0].type = "Fire";
	mainCar.userSpells[1].name = "Lightning Bolt";
	mainCar.userSpells[1].damage = 4;
	mainCar.userSpells[1].type = "Electric";
	mainCar.userSpells[2].name = "Poison Cloud";
	mainCar.userSpells[2].damage = 3;
	mainCar.userSpells[2].type = "Poison";
	mainCar.userPotions[0].name = NULL;
	mainCar.userPotions[1].name = NULL;
	mainCar.userPotions[2].name = NULL;
	mainCar.userPotions[3].name = NULL;
	mainCar.userPotions[4].name = NULL;
	
	//generateChar(&mainCar);
	createWeapons(weaponList);
	
	do {
		
		dungeon1[charLoc[0]][charLoc[1]] = '*'; //Character placement
		switch(mapNum){
			case 1:
				printf("Dungeon\n");
				break;
			case 2:
				printf("Evergreen City\n");
				if(newMap) {
					charLoc[0] = 2;
					charLoc[1] = 41;
					newMap = false;
				}
				break;
			case 3:
				printf("Evergreen Forests\n");
				if(newMap) {
					charLoc[0] = 1;
					charLoc[1] = rand()%148+1;
					newMap = false;
				}
				break;
			case 4:
				printf("Neverwinter Mountain\n");
				if(newMap) {
					charLoc[0] = 10;
					charLoc[1] = 2;
					newMap = false;
				}
				break;

			case 5:
				printf("Everflowing Volcanoe\n");
				if(newMap) {
					charLoc[0] = 35;
					charLoc[1] = 2;
					newMap = false;
				}
				break;

		}
		
		if(invalidMove) {
			printf("You're trying to make an invalid move. \n");
		} else if (invalid) {
			printf("No valid input made. \n");
		} else if (inventoryDisplay) { // %d damage, %s type. Weapon 2: %s, %d damage, %s type.\n"
			printf("Health: %d / %d, Level: %d, Weapon 1: %s, %d damage, %s type. Weapon 2: %s, %d damage, %s type.\n",mainCar.userCurHp,mainCar.userMaxHp,mainCar.lvl,mainCar.userWeapons[0].name,mainCar.userWeapons[0].damage,mainCar.userWeapons[0].type,mainCar.userWeapons[1].name,mainCar.userWeapons[1].damage,mainCar.userWeapons[1].type);
		} else if (healed) {
			printf("You have been healed to max HP.\n");
		} else {
			printf("\n");
		}
		inventoryDisplay = false;
		invalidMove = false;
		invalid = false;
		healed = false;
		
		switch(mapNum) {
			case 1:
				for(i = 0; i < 26; i++) { //Map Display
					printf(dungeon1[i]);
					printf("\n");
				}
				break;
			case 2:
				for(i = 0; i < 40; i++) {
					printf(dungeon2[i]);
					printf("\n");
				}
				break;
			case 3:
				for(i = 0; i < 50; i++) {
					printf(dungeon2[i]);
					printf("\n");
				}
				break;
			case 4:
				for(i = 0; i < 37; i++) {
					printf(dungeon2[i]);
					printf("\n");
				}
				break;
			case 5:
				for(i = 0; i < 36; i++) {
					printf(dungeon2[i]);
					printf("\n");
				}
				break;
		}
		printf("Input: ");
	//	scanf(" %c",&input);
		input = getch();
		clrscr();
		
		if ( input == 'w' || input == 'W') {
			if(canMove(charLoc, 1)) {
				
				dungeon1[charLoc[0]][charLoc[1]] = lastChar;
				charLoc[0]--;
				lastChar = dungeon1[charLoc[0]][charLoc[1]];
				if(lastChar == '_') {
					mainCar.userCurHp = mainCar.userMaxHp;
					healed = true;
				} else if (lastChar == 'E'){
					mapNum++;
					newMap = true;
					mapDisplay = false;
				}
			} else {
				invalidMove = true;
				invalidMove = loot(charLoc,1, weaponList, &mainCar);
				if(!invalidMove) continue;
				invalidMove = combatTrigger(charLoc, 1, mapNum, &mainCar);
			}
			invalid = false;
		} else if ( input == 'a' || input == 'A') {
			if(canMove(charLoc, 2)) {
				dungeon1[charLoc[0]][charLoc[1]] = lastChar;
				charLoc[1]--;
				lastChar = dungeon1[charLoc[0]][charLoc[1]];
				if(lastChar == '_') {
					mainCar.userCurHp = mainCar.userMaxHp;
					healed = true;
				} else if (lastChar == 'E'){
					mapNum++;
					newMap = true;
					mapDisplay = false;
				}
			} else {
				invalidMove = true;
				invalidMove = loot(charLoc, 2, weaponList, &mainCar);
				if(!invalidMove) continue;
				invalidMove = combatTrigger(charLoc,2,mapNum,&mainCar);
				
			}
			invalid = false;
		} else if ( input == 's' || input == 'S') {
			if(canMove(charLoc, 3)) {
				
				dungeon1[charLoc[0]][charLoc[1]] = lastChar;
				charLoc[0]++;
				lastChar = dungeon1[charLoc[0]][charLoc[1]];
				if(lastChar == '_') {
					mainCar.userCurHp = mainCar.userMaxHp;
					healed = true;
				} else if (lastChar == 'E'){
					mapNum++;
					newMap = true;
					mapDisplay = false;
				}
			} else {
				invalidMove = true;
				invalidMove = loot(charLoc, 3, weaponList, &mainCar);
				if(!invalidMove) continue;
				invalidMove = combatTrigger(charLoc,3,mapNum,&mainCar);
				
			}
			invalid = false;
		} else if ( input == 'd' || input == 'D') {
			if(canMove(charLoc, 4)) {
			
				dungeon1[charLoc[0]][charLoc[1]] = lastChar;
				charLoc[1]++;
				lastChar = dungeon1[charLoc[0]][charLoc[1]];
				if(lastChar == '_') {
					mainCar.userCurHp = mainCar.userMaxHp;
					healed = true;
				} else if (lastChar == 'E'){
					mapNum++;
					newMap = true;
					mapDisplay = false;
					
				}
			} else {
				invalidMove = true;
				invalidMove = loot(charLoc, 4, weaponList, &mainCar);
				if(!invalidMove) continue;
				invalidMove = combatTrigger(charLoc,4,mapNum,&mainCar);
			}
		} else if ( input == 'i' || input == 'I') {
			inventoryDisplay = true;
		} else {
			invalid = true;
		}
	} while (mapDisplay);
	printf("Thanks for playing the Dungeon Adventure Demo!");
}
