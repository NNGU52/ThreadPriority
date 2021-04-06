# ThreadPriority
Управление потоками.

## Постановка задачи
Управление потоками. В процессе создано 3 потока: первичный, управляющий графическим интерфейсом пользователя, и ДВА вторичных потока, выполняющих произвольную работу в бесконечном цикле. Для оценки своей производительности вторичные потоки подсчитывают количество выполненной работы в каких-либо единицах. Первичный поток периодически запрашивает данные о количестве работы, выполненной вторичными потоками в единицу времени, и отображает эти данные на экране. Предусмотреть возможность изменения относительных приоритетов вторичных потоков. Изучить, как изменение приоритетов влияет на относительную производительность вторичных потоков. **Дополнение:** вызвать во вторичном потоке функцию Sleep(0) после выполнения единицы работы. Изучить, как изменяется производительность потока в этом случае.

## Интерфейс программы
Потоки с одинаковым приоритетом:
<p align="center"><img src="https://github.com/NNGU52/ThreadPriority/blob/main/screenshots/1.png"/></p>

Потоки с разными приоритетами:
<p align="center"><img src="https://github.com/NNGU52/ThreadPriority/blob/main/screenshots/2.png"/></p>

Первый поток вызывает функцию Sleep(0) после каждой единицы работы. Видно, что его производительность упала почти до нуля. Из документации Microsoft:
> A value of zero causes the thread to relinquish the remainder of its time slice to any other thread that is ready to run. If there are no other threads ready to run, the function returns immediately, and the thread continues execution.  
>  
> Windows XP/2000: A value of zero causes the thread to relinquish the remainder of its time slice to any other thread of equal priority that is ready to run. If there are no other threads of equal priority ready to run, the function returns immediately, and the thread continues execution. This behavior changed starting with Windows Server 2003.
<p align="center"><img src="https://github.com/NNGU52/ThreadPriority/blob/main/screenshots/3.png"/></p>

### P.S.
Visual Studio 2013, MFC
