#include "producer.h"
#include "dispatcher.h"
#include "co_editor.h"
#include "screen_manager.h"
#include "filereader.h"
#include "unbounded_buffer.h"
#include "runnable.h"
#include <pthread.h>

// gcc -pthread mainflow.c

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./ex3.out filename\n");
        return 1; // Return an error code to indicate incorrect usage
    }

    char *filename = argv[1];
    int num_producers = linesCount(filename) / 4;
    Producer **producers = malloc(num_producers * sizeof(Producer *));
    if (producers == NULL)
    {
        printf("malloc failed\n");
        return 1;
    }
    int co_editor_queue_size = 0;

    if (readData(filename, producers, num_producers, &co_editor_queue_size) != 0)
    {
        printf("malloc failed\n");
        goto fail_1;
    }
    Dispatcher *dispatcher = createDispatcher(producers, num_producers);
    if (dispatcher == NULL)
    {
        printf("malloc failed\n");
        goto fail_2;
    }
    Screen_Manager *screen_manager = createScreenManager(co_editor_queue_size);
    if (screen_manager == NULL)
    {
        printf("malloc failed\n");
        goto fail_3;
    }
    Co_Editor **co_editors = malloc(3 * sizeof(Co_Editor *));
    if (co_editors == NULL)
    {
        printf("malloc failed\n");
        goto fail_4;
    }
    co_editors[0] = createCoEditor(screen_manager->buffer, dispatcher->ubb_N);
    if (co_editors[0] == NULL)
    {
        printf("malloc failed\n");
        goto fail_5;
    }
    co_editors[1] = createCoEditor(screen_manager->buffer, dispatcher->ubb_W);
    if (co_editors[1] == NULL)
    {
        printf("malloc failed\n");
        goto fail_6;
    }
    co_editors[2] = createCoEditor(screen_manager->buffer, dispatcher->ubb_S);
    if (co_editors[2] == NULL)
    {
        printf("malloc failed\n");
        goto fail_7;
    }
    Runnable **runnable = malloc((5 + num_producers) * sizeof(Runnable *));
    if (runnable == NULL)
    {
        printf("malloc failed\n");
        goto fail_8;
    }
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
    if (thread_id == NULL)
    {
        printf("malloc failed\n");
        goto fail_9;
    }
    for (int i = 0; i < 5 + num_producers; i++)
    {
        pthread_create(&thread_id[i], NULL, runnable[i]->run, (void *)runnable[i]);
    }
    for (int i = 0; i < 5 + num_producers; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

fail_9:
    free(thread_id);
fail_8:
    free(runnable);
fail_7:
    destroyCoEditor(co_editors[2]);
fail_6:
    destroyCoEditor(co_editors[1]);
fail_5:
    destroyCoEditor(co_editors[0]);
fail_4:
    free(co_editors);
fail_3:
    destroyScreenManager(screen_manager);
fail_2:
    destroyDispatcher(dispatcher);
    for (int i = 0; i < num_producers; i++)
    {
        destroyProducer(producers[i]);
    }
fail_1:
    free(producers);
    return 0;
}