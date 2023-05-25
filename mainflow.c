#include "producer.h"
#include "dispatcher.h"
#include "co_editor.h"
#include "screen_manager.h"
#include "filereader.h"
#include "unbounded_buffer.h"
#include "runnable.h"
#include <pthread.h>

// gcc -pthread mainflow.c

int main()
{
    char *filename = "conf.txt";
    int num_producers = linesCount(filename) / 4;
    Producer **producers = malloc(num_producers * sizeof(Producer *));
    int co_editor_queue_size = 0;

    readData(filename, producers, num_producers, &co_editor_queue_size);

    Dispatcher *dispatcher = createDispatcher(producers, num_producers);
    Screen_Manager *screen_manager = createScreenManager(co_editor_queue_size);
    Co_Editor **co_editors = malloc(3 * sizeof(Co_Editor *));
    co_editors[0] = createCoEditor(screen_manager->buffer, dispatcher->ubb_N);
    co_editors[1] = createCoEditor(screen_manager->buffer, dispatcher->ubb_W);
    co_editors[2] = createCoEditor(screen_manager->buffer, dispatcher->ubb_S);

    Runnable **runnable = malloc((5 + num_producers) * sizeof(Runnable *));
    runnable[0] = (Runnable *)dispatcher;
    runnable[1] = (Runnable *)screen_manager;
    runnable[2] = (Runnable *)co_editors[0];
    runnable[3] = (Runnable *)co_editors[1];
    runnable[4] = (Runnable *)co_editors[2];
    for (int i = 0; i < num_producers; i++)
    {
        runnable[5 + i] = (Runnable *)producers[i];
    }
    pthread_t *thread_id = malloc((5 + num_producers) * sizeof(pthread_t));
    for (int i = 0; i < 5 + num_producers; i++)
    {
        pthread_create(&thread_id[i], NULL, runnable[i]->run, (void *)runnable[i]);
    }
    for (int i = 0; i < 5 + num_producers; i++)
    {
        pthread_join(thread_id[i], NULL);
    }
    // destroy for screen_manager
    destroyScreenManager(screen_manager);
    // destroy for co_editors
    for (int i = 0; i < 3; i++)
    {
        destroyCoEditor(co_editors[i]);
    }
    // destroy dispatcher
    destroyDispatcher(dispatcher);
    // destroy for producers
    for (int i = 0; i < num_producers; i++)
    {
        destroyProducer(producers[i]);
    }
    free(producers);
    free(co_editors);
    free(runnable);

    return 0;
}