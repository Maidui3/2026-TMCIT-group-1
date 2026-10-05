#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/* ==============================
   プレイヤー
============================== */
typedef struct {
    char name[32];

    int level;
    int exp;

    int hp;
    int max_hp;

    int mp;
    int max_mp;

    int attack;
    int defense;

    int gold;
} Player;


/* ==============================
   敵
============================== */
typedef struct {
    char name[32];

    int hp;
    int max_hp;

    int attack;
    int defense;

    int exp;
    int gold;
} Enemy;


/* ==============================
   入力バッファを空にする
============================== */
void clear_input(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}


/* ==============================
   プレイヤーステータス表示
============================== */
void show_status(Player *p)
{
    printf("\n");
    printf("====================================\n");
    printf("           プレイヤーステータス\n");
    printf("====================================\n");

    printf("名前      : %s\n", p->name);
    printf("レベル    : %d\n", p->level);
    printf("経験値    : %d / %d\n",
           p->exp, p->level * 100);

    printf("HP        : %d / %d\n",
           p->hp, p->max_hp);

    printf("MP        : %d / %d\n",
           p->mp, p->max_mp);

    printf("攻撃力    : %d\n", p->attack);
    printf("防御力    : %d\n", p->defense);
    printf("所持金    : %d G\n", p->gold);

    printf("====================================\n");
}


/* ==============================
   レベルアップ
============================== */
void check_level_up(Player *p)
{
    int required_exp;

    while (1) {

        required_exp = p->level * 100;

        if (p->exp < required_exp)
            break;

        p->exp -= required_exp;

        p->level++;

        p->max_hp += 20;
        p->max_mp += 5;

        p->attack += 5;
        p->defense += 3;

        p->hp = p->max_hp;
        p->mp = p->max_mp;

        printf("\n");
        printf("************************************\n");
        printf("          ★ レベルアップ！ ★\n");
        printf("************************************\n");

        printf("レベルが %d になった！\n", p->level);
        printf("最大HPが20上昇した！\n");
        printf("最大MPが5上昇した！\n");
        printf("攻撃力が5上昇した！\n");
        printf("防御力が3上昇した！\n");

        printf("HPとMPが全回復した！\n");

        printf("************************************\n");
    }
}


/* ==============================
   敵をランダム生成
============================== */
Enemy create_enemy(Player *p)
{
    Enemy e;

    int type;

    type = rand() % 4;


    /* スライム */
    if (type == 0) {

        sprintf(e.name, "スライム");

        e.max_hp = 30 + p->level * 5;
        e.attack = 8 + p->level * 2;
        e.defense = 2 + p->level;

        e.exp = 30 + p->level * 5;
        e.gold = 10 + rand() % 20;
    }


    /* ゴブリン */
    else if (type == 1) {

        sprintf(e.name, "ゴブリン");

        e.max_hp = 45 + p->level * 7;
        e.attack = 12 + p->level * 2;
        e.defense = 4 + p->level;

        e.exp = 45 + p->level * 6;
        e.gold = 20 + rand() % 30;
    }


    /* オオカミ */
    else if (type == 2) {

        sprintf(e.name, "オオカミ");

        e.max_hp = 55 + p->level * 8;
        e.attack = 15 + p->level * 3;
        e.defense = 3 + p->level;

        e.exp = 55 + p->level * 7;
        e.gold = 25 + rand() % 30;
    }


    /* オーク */
    else {

        sprintf(e.name, "オーク");

        e.max_hp = 70 + p->level * 10;
        e.attack = 18 + p->level * 3;
        e.defense = 7 + p->level;

        e.exp = 70 + p->level * 8;
        e.gold = 30 + rand() % 40;
    }

    e.hp = e.max_hp;

    return e;
}


/* ==============================
   敵ステータス表示
============================== */
void show_enemy(Enemy *e)
{
    printf("\n");
    printf("------------------------------------\n");

    printf("敵 : %s\n", e->name);

    printf("HP : %d / %d\n",
           e->hp, e->max_hp);

    printf("------------------------------------\n");
}


/* ==============================
   回復魔法
============================== */
void heal(Player *p)
{
    int heal_amount;

    if (p->mp < 5) {

        printf("\nMPが足りない！\n");

        return;
    }


    if (p->hp == p->max_hp) {

        printf("\nHPはすでに満タンだ！\n");

        return;
    }


    p->mp -= 5;

    heal_amount = 25 + p->level * 5;

    p->hp += heal_amount;


    if (p->hp > p->max_hp)
        p->hp = p->max_hp;


    printf("\n");
    printf("回復魔法を使った！\n");

    printf("HPが %d 回復した！\n",
           heal_amount);
}


/* ==============================
   プレイヤーの攻撃
============================== */
void player_attack(Player *p, Enemy *e)
{
    int damage;

    damage = p->attack - e->defense;


    if (damage < 1)
        damage = 1;


    /* 10%でクリティカル */
    if (rand() % 10 == 0) {

        damage *= 2;

        printf("\n");
        printf("★★★ クリティカルヒット！ ★★★\n");
    }


    e->hp -= damage;


    if (e->hp < 0)
        e->hp = 0;


    printf("\n");
    printf("%s に %d ダメージ！\n",
           e->name,
           damage);
}


/* ==============================
   敵の攻撃
============================== */
void enemy_attack(Player *p, Enemy *e)
{
    int damage;

    damage = e->attack - p->defense;


    if (damage < 1)
        damage = 1;


    p->hp -= damage;


    if (p->hp < 0)
        p->hp = 0;


    printf("\n");

    printf("%s の攻撃！\n",
           e->name);

    printf("%d ダメージを受けた！\n",
           damage);
}


/* ==============================
   通常戦闘
============================== */
int battle(Player *p)
{
    Enemy enemy;

    int command;


    enemy = create_enemy(p);


    printf("\n");
    printf("====================================\n");

    printf("        %s が現れた！\n",
           enemy.name);

    printf("====================================\n");


    while (p->hp > 0 && enemy.hp > 0) {

        printf("\n");

        printf("あなた HP : %d / %d\n",
               p->hp,
               p->max_hp);

        printf("あなた MP : %d / %d\n",
               p->mp,
               p->max_mp);


        show_enemy(&enemy);


        printf("\n");
        printf("[1] 攻撃\n");
        printf("[2] 回復魔法\n");
        printf("[3] 逃げる\n");

        printf("\n>> ");


        if (scanf("%d", &command) != 1) {

            clear_input();

            printf("数字を入力してください。\n");

            continue;
        }


        /* 攻撃 */
        if (command == 1) {

            player_attack(p, &enemy);
        }


        /* 回復 */
        else if (command == 2) {

            heal(p);
        }


        /* 逃走 */
        else if (command == 3) {

            if (rand() % 2 == 0) {

                printf("\n");
                printf("うまく逃げ切った！\n");

                return 0;
            }

            else {

                printf("\n");
                printf("逃げられなかった！\n");
            }
        }


        else {

            printf("\n");
            printf("そのコマンドはありません。\n");

            continue;
        }


        /* 敵が倒された */
        if (enemy.hp <= 0)
            break;


        /* 敵の攻撃 */
        enemy_attack(p, &enemy);
    }


    /* プレイヤー死亡 */
    if (p->hp <= 0) {

        printf("\n");
        printf("====================================\n");
        printf("              GAME OVER\n");
        printf("====================================\n");

        return -1;
    }


    /* 勝利 */
    printf("\n");
    printf("====================================\n");
    printf("                勝利！\n");
    printf("====================================\n");

    printf("%s を倒した！\n",
           enemy.name);

    printf("経験値 +%d\n",
           enemy.exp);

    printf("ゴールド +%d G\n",
           enemy.gold);


    p->exp += enemy.exp;
    p->gold += enemy.gold;


    check_level_up(p);


    return 1;
}


/* ==============================
   魔王戦
============================== */
int boss_battle(Player *p)
{
    Enemy boss;

    int command;
    int damage;


    sprintf(boss.name, "魔王");


    boss.max_hp = 350 + p->level * 30;
    boss.hp = boss.max_hp;

    boss.attack = 30 + p->level * 4;
    boss.defense = 10 + p->level * 2;

    boss.exp = 500;
    boss.gold = 1000;


    printf("\n");
    printf("####################################\n");
    printf("#                                  #\n");
    printf("#          ★ 魔王が現れた！ ★      #\n");
    printf("#                                  #\n");
    printf("####################################\n");


    while (p->hp > 0 && boss.hp > 0) {

        printf("\n");

        printf("------------------------------------\n");

        printf("あなた HP : %d / %d\n",
               p->hp,
               p->max_hp);

        printf("あなた MP : %d / %d\n",
               p->mp,
               p->max_mp);

        printf("魔王 HP   : %d / %d\n",
               boss.hp,
               boss.max_hp);

        printf("------------------------------------\n");


        printf("\n");

        printf("[1] 攻撃\n");
        printf("[2] 回復魔法\n");

        printf("\n>> ");


        if (scanf("%d", &command) != 1) {

            clear_input();

            continue;
        }


        /* 攻撃 */
        if (command == 1) {

            damage = p->attack - boss.defense;


            if (damage < 1)
                damage = 1;


            if (rand() % 10 == 0) {

                damage *= 2;

                printf("\n");
                printf("★★★ クリティカルヒット！ ★★★\n");
            }


            boss.hp -= damage;


            if (boss.hp < 0)
                boss.hp = 0;


            printf("\n");

            printf("魔王に %d ダメージ！\n",
                   damage);
        }


        /* 回復 */
        else if (command == 2) {

            heal(p);
        }


        else {

            printf("そのコマンドはありません。\n");

            continue;
        }


        /* 魔王撃破 */
        if (boss.hp <= 0)
            break;


        /* 魔王の攻撃 */

        damage = boss.attack - p->defense;


        if (damage < 1)
            damage = 1;


        /* 20%で必殺技 */
        if (rand() % 5 == 0) {

            damage *= 2;

            printf("\n");
            printf("！！！！ 魔王の必殺技 ！！！！\n");
        }


        p->hp -= damage;


        if (p->hp < 0)
            p->hp = 0;


        printf("\n");

        printf("魔王から %d ダメージを受けた！\n",
               damage);
    }


    /* 敗北 */
    if (p->hp <= 0) {

        printf("\n");
        printf("####################################\n");
        printf("#                                  #\n");
        printf("#             GAME OVER            #\n");
        printf("#                                  #\n");
        printf("####################################\n");

        return 0;
    }


    /* 勝利 */
    printf("\n");

    printf("####################################\n");
    printf("#                                  #\n");
    printf("#       ★★ 魔王を倒した！！ ★★    #\n");
    printf("#                                  #\n");
    printf("####################################\n");


    printf("\n");
    printf("経験値 +%d\n", boss.exp);
    printf("ゴールド +%d G\n", boss.gold);


    return 1;
}


/* ==============================
   メイン
============================== */
int main(void)
{
    Player player;

    int command;
    int result;


    /*
       WindowsコンソールをUTF-8に設定

       ソースコードもUTF-8で保存してください。
    */
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    /* 乱数初期化 */
    srand((unsigned int)time(NULL));


    /* 初期ステータス */

    player.level = 1;
    player.exp = 0;

    player.max_hp = 100;
    player.hp = player.max_hp;

    player.max_mp = 30;
    player.mp = player.max_mp;

    player.attack = 20;
    player.defense = 8;

    player.gold = 100;


    /* タイトル */

    printf("\n");

    printf("====================================\n");
    printf("                                    \n");
    printf("          C言語 RPG GAME            \n");
    printf("                                    \n");
    printf("====================================\n");


    /* 名前入力 */

    printf("\n");
    printf("あなたの名前を入力してください：");

    scanf("%31s", player.name);


    printf("\n");
    printf("%s の冒険が始まる！\n",
           player.name);


    /* メインループ */

    while (1) {

        printf("\n");

        printf("====================================\n");
        printf("               MENU\n");
        printf("====================================\n");

        printf("[1] 冒険に出る\n");
        printf("[2] ステータスを見る\n");
        printf("[3] 宿屋に泊まる（20G）\n");
        printf("[4] 魔王城へ行く\n");
        printf("[5] ゲーム終了\n");

        printf("====================================\n");

        printf(">> ");


        if (scanf("%d", &command) != 1) {

            clear_input();

            printf("数字を入力してください。\n");

            continue;
        }


        /* ==========================
           冒険
        ========================== */

        if (command == 1) {

            printf("\n");
            printf("フィールドを探索している...\n");


            /*
               75%で敵
               25%で宝箱
            */

            if (rand() % 100 < 75) {

                result = battle(&player);


                if (result == -1)
                    return 0;
            }

            else {

                int treasure;

                treasure = 20 + rand() % 80;


                printf("\n");
                printf("宝箱を発見した！\n");

                printf("%d Gを手に入れた！\n",
                       treasure);


                player.gold += treasure;
            }
        }


        /* ==========================
           ステータス
        ========================== */

        else if (command == 2) {

            show_status(&player);
        }


        /* ==========================
           宿屋
        ========================== */

        else if (command == 3) {

            if (player.gold < 20) {

                printf("\n");
                printf("お金が足りない！\n");
            }

            else {

                player.gold -= 20;

                player.hp = player.max_hp;
                player.mp = player.max_mp;


                printf("\n");
                printf("宿屋で休んだ。\n");
                printf("HPとMPが全回復した！\n");
            }
        }


        /* ==========================
           魔王城
        ========================== */

        else if (command == 4) {

            if (player.level < 5) {

                printf("\n");

                printf("魔王城の門番\n");

                printf("「まだ魔王と戦うには早すぎる！」\n");

                printf("「Lv5以上になってから来い！」\n");
            }

            else {

                printf("\n");
                printf("魔王城へ入った...\n");


                result = boss_battle(&player);


                if (result == 1) {

                    printf("\n");

                    printf("====================================\n");
                    printf("               ENDING\n");
                    printf("====================================\n");

                    printf("%s は世界を救った！\n",
                           player.name);

                    printf("\n");
                    printf("おめでとう！！\n");

                    printf("====================================\n");

                    return 0;
                }

                else {

                    return 0;
                }
            }
        }


        /* ==========================
           ゲーム終了
        ========================== */

        else if (command == 5) {

            printf("\n");
            printf("ゲームを終了します。\n");

            return 0;
        }


        else {

            printf("\n");
            printf("そのコマンドはありません。\n");
        }
    }


    return 0;
}