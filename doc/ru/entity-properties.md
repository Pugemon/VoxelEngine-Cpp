# Свойства сущностей

## Логика

### Cписок компонентов - *components*

Определяет компоненты и порядок их инициализации.

```json
"components": [
    список компонентов
]
```

Пример:

```json
"components": [
    "base:drop"
]
```

Код компонентов должен находиться в `scripts/components`.

## Физика

### Хитбокс - *hitbox*

Массив из трех чисел, указывающих размер хитбокса сущности.

Пример:

```json
"hitbox": [0.6, 1.8, 0.6]
```


### Тип тела - *body-type*

Определяет то, как с ним будет работать физический движок.

- *dynamic* (динамический) - тип по-умолчанию. Физический движок просчитывает движение и столкновения.
- *kinematic* (кинематический) - просчитывается только движение, без столкновений.

### Блокирование - *blocking*

Определяет блокирует ли сущность установку блоков.

*В будущем будет также блокировать движение других сущностей.*

Значение по-умолчанию: *true*.

### Список сенсоров - *sensors*

Сенсор - область пространства, привязанная к физическому телу, детектирующее попадание в него других тел.

- При попадании тела вызывается событие *on_sensor_enter*.
- При покидании тела вызывается событие *on_sensor_exit*.

Сенсоры индексируются в том же порядке, в каком представлены в списке, начиная с 0.

Существуют следующие типы (формы) сенсоров:
- radius (радиус) - самый простой сенсор. Определяет область вокруг центра хитбокса. Указываются следующие значения:
    - радиус - число.
- aabb (коробка) - прямоугольная область, меняющая положение в зависимости от поворота сущности. **Сама область не поворачивается.** Указываются следующие значения:
    - три числа x, y, z минимального угла области.
    - три числа x, y, z противоположного угла области.

Пример:

```json
"sensors": [
    ["aabb", -0.2, -0.2, -0.2, 0.2, 0.2, 0.2],
    ["radius", 1.6]
]
```

0. Прямоугольная область шириной, высотой и длиной в 0.4 м. с центром в 0.0.
1. Радиальная область с радиусом 1.6 м.

## Вид

### Имя скелета - *skeleton-name*

Значение по-умолчанию совпадает с именем сущности. Определяет то, какой скелет будет использоваться сущностью. См. [риггинг](rigging.md).

## Сохранение/загрузка

Кроме данных пользовательских компонентов, движок автоматически сохраняет данные встроенных: transform, rigidbody, skeleton.

Есть набор флагов, позволяющих указать какие данные будут сохранены, а какие нет.

(Указываются булевы значения)

| Название               | Цель                                                     | По-умолчанию |
| ---------------------- | -------------------------------------------------------- | ------------ |
| save                   | сама сущность                                            | true         |
| save-skeleton-pose     | поза скелета сущности                                    | false        |
| save-skeleton-textures | динамически назначенные текстуры                         | false        |
| save-body-velocity     | скорость движения тела                                   | true         |
| save-body-settings     | измененные настройки тела <br>(type, damping, crouching) | false        |