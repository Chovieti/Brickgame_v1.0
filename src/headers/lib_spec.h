#ifndef LIB_SPEC_H
#define LIB_SPEC_H

#include <stdbool.h>

/**
 * @enum UserAction_t
 * @brief Перечисление возможных действий пользователя.
 *
 * Данный enum описывает все допустимые действия, которые пользователь может
 * выполнить в игре.
 */
typedef enum {
  Start,     /**< Начало игры.*/
  Pause,     /**< Пауза.*/
  Terminate, /**< Завершение игры.*/
  Left,      /**< Движение влево.*/
  Right,     /**< Движение вправо.*/
  Up,        /**< Движение вверх.*/
  Down,      /**< Движение вниз.*/
  Action     /**< Действие.*/
} UserAction_t;

/**
 * @struct GameInfo_t
 * @brief Структура для хранения информации об игре для отрисовки.
 *
 * Хранит различные параметры игры, такие как поле, следующую фигуру, очки,
 * текущий уровень и т.д.
 */
typedef struct {
  int **field; /**< Указатель на текущее поле.*/
  int **next;  /**< Указатель на следующую фигуру.*/
  int score;   /**< Текущий счет.*/
  int high_score; /**< Рекорд.*/
  int level;      /**< Текущий уровень.*/
  int speed;      /**< Скорость падения фигур.*/
  int pause;      /**< Пауза (1 - пауза, 0 - игра идет).*/
} GameInfo_t;

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif