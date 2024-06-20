## String.h
#### Написали этот проект совместно: [kunlxo](https://github.com/kunlxo), [erik2nd](https://github.com/erik2nd), [flambdaf](https://github.com/flambdaf)
- Для будущих студентов школы 21: не советую этот код брать и копировать(касается sscanf, sprintf)
- Во первых, в нем есть свои проблемы, такие как conditional jump(то есть некторые тесты заваливаются)
- Во вторых, это не этично. Мне попалась однажды команда, которая скопировала полностью sprintf от московских студентов(ролик можно найти на ютубе по запросу s21_string.h).
- Я этим людям не поставил флаг cheat. Но было неприятно видеть, что люди подобным занимаются. Пишите свой код 
#### По поводу самого проекта:
- Собирается с помощью Makefile'a, есть цель gcov_report, которая показывает покрытие всех функций(очень полезная штука).
- Есть цель s21_string.a, которая собирает статическую библиотеку
- Цель тест: собирает проект и запускает все тесты для каждой функции

#### sscanf делал [kunlxo](https://github.com/kunlxo), sprintf - mxkxrskx, Makefile - [erik2nd](https://github.com/erik2nd)
#### [flambdaf](https://github.com/flambdaf) : strtok(), strncmp(), strncpy(), to_lower(), to_upper()
#### [kunlxo](https://github.com/kunlxo) : strncat(), memset()
#### [erik2nd](https://github.com/erik2nd) : strcspn(), strrchr(), strstr(), insert(), trim()
#### mxkxrskx : strerror(), memcpy(), strlen(), strchr(), strpbrk()
