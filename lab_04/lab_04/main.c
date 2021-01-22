#include "funcs.h"

int main()
{
    int result = SUCCESS;
    setbuf(stdout, NULL);

    //Инициализация стека(массив)
    stack_t *stack = NULL;
    stack = init();

    //инициализация стека(Список)
    Stack_t *lstack = NULL;

    adress_t *adress = adress_init();

    show_title(1);
    result = stack_menu();

    while (result == ERROR)
    {
        printf("Некорректный ввод.\n");
        show_title(1);
        result = stack_menu();
    }

    if (result == 1)
        while (result != EXIT)
        {
            show_title(2);
            result = do_menu(stack);
        }
    else
        while (result != EXIT)
        {
            show_title(3);
            result = do_lmenu(&lstack, adress);
        }

    return result;
}
