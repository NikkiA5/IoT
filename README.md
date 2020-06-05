# Идея: устройство, которое будет измерять температуру воздуха и количество газа в воздухе.
# Кому это нужно? 
# Кто не ругался с соседом в общежитии из-за графика проветриваний, кто не волновался за невыключенную газовую плиту?
# Такое было у всех, теперь это можно проверять и удалённо, а также иметь весомые аргументы в споре  соседом.
# В файле sheme.png есть схема устройства, которое базируется на arduino uno. В устройстве имеются: датчик температуры воздуха TMP36, датчик газа(предположительн, MQ-2), 3 светодиода(красный, жёлтый и зелёный), вайфпй модуль ESP8266. Для оптимальности использована макетная плата.
# Светодиоды говорят пользователю общую оценку воздуха в комнате по шкале плохо, терпимо и хорошо в соответствии с вышеописанными цветами.
# В файле arduino.cpp находится код работы для схемы из файла, который описан выше. Он включает в себя часть прошивки вайфая.
# Гипотетически представим у себя наличие сервера, в его отсутствие сделаем вид, что tinkercad умеет записывать в файл данные. Имея файл с данными, можно устроить работу веб-сервиса для удалённого анализа работы устройства.
# В файле web.py код веб-страницы, которая позволяет пройти аутентификацию, увидеть графики изменения температуры и газа в течение последних 11 часов.
