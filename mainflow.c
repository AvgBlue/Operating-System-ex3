#include "producer.h"
#include "dispatcher.h"
#include "co_editor.h"
#include "screen_manager.h"
#include "filereader.h"

int main()
{
    char *filename = "conf.txt";
    int num_producers = linesCount(filename) / 4;
    Producer **producers = malloc(num_producers * sizeof(Producer *));
    int co_editor_queue_size = 0;

    readData(filename, producers, num_producers, &co_editor_queue_size);
    // print
    printf("num_producers: %d\n", num_producers);
    printf("co_editor_queue_size: %d\n", co_editor_queue_size);
    for (int i = 0; i < num_producers; i++)
    {
        printf("producer %d:\n", i);
        printf("    producer_id: %d\n", producers[i]->id);
        printf("    producer_type: %d\n", producers[i]->numProducts);
        printf("    producer_delay: %d\n", producers[i]->queueSize);
    }

    Dispatcher *dispatcher = createDispatcher(producers, num_producers);
    Screen_Manager *screen_manager = createScreenManager(co_editor_queue_size);
    Co_Editor **co_editors = malloc(3 * sizeof(Co_Editor *));
    co_editors[0] = createCoEditor(screen_manager->buffer, dispatcher->ubb_N);
    co_editors[1] = createCoEditor(screen_manager->buffer, dispatcher->ubb_W);
    co_editors[2] = createCoEditor(screen_manager->buffer, dispatcher->ubb_S);

    // start producers
    for (int i = 0; i < num_producers; i++)
    {
        start_Producer(producers[i]);
    }
    printf("All producers are done.\n");
    // start dispatcher
    start_Dispatcher(dispatcher);
    printf("Dispatcher is done.\n");
    // start co-editors
    for (int i = 0; i < 3; i++)
    {
        start_Co_Editor(co_editors[i]);
    }
    printf("All co-editors are done.\n");
    // start screen manager
    start_Screen_Managar(screen_manager);
    printf("Screen manager is done.\n");

    // destroy dispatcher
    destroyDispatcher(dispatcher);
    // destroy for producers
    for (int i = 0; i < num_producers; i++)
    {
        destroyProducer(producers[i]);
    }
    free(producers);

    return 0;
}