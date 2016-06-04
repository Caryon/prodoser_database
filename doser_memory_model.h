#ifndef PRODOSERMEMORYMODEL_H
#define PRODOSERMEMORYMODEL_H

#include <cstdint>

union ShortTime
{
    struct {
        int16_t day, month, year, hour, minute;
    };
    int16_t a[5];
} __attribute__((packed));

struct Weight
{
    float weight;
    ShortTime time;
    int16_t component; // component number
} __attribute__((packed));

struct Command
{
    uint8_t command; //code_of_command
    uint8_t channel; //apply_to_channel
} __attribute__((packed));

struct DoserMemoryModel
{
    enum {
        ComponentsMumber = 16,
        InputsNumber = 24,
        OutputsNumber = 16,
        TimersNumber = 16,
        CountersNumber = 8,
        MemoryWeightsNumber = 40,
        CommandPerInput = 6,
        CompletionCommandsNumber = OutputsNumber + TimersNumber + CountersNumber,
    };

    struct DoserParameters
    {
        float threshold1[OutputsNumber];
        float threshold2[OutputsNumber];
        float adjust[OutputsNumber];
        uint32_t init_output; // начальное состояние
        uint32_t relational_mode; // относительное / абсолютное дозирование
        uint32_t unload;      // разгрузка = 1, загрузка = 0
    } __attribute__((packed)); // параметры рабочих каналов

    float currentWeight; //weight.weight copy
    int16_t commandRegister; //RS232 operation
    int16_t showError;

    DoserParameters parameters; // параметры рабочих каналов
    float timer[TimersNumber]; // параметры таймеров
    uint16_t counter[CountersNumber]; // параметры счетчиков

    Command outCommand[CompletionCommandsNumber];
    Command inputCommand[InputsNumber][CommandPerInput]; // команды рабочих каналов

   Weight component[ComponentsMumber]; // раздельное покомпонентное суммирование
   Weight lastWeights[MemoryWeightsNumber]; // последние отвесы

   int16_t weight_mem_p;    // указатель на последние сохраненные отвесы

   uint64_t totalWeightsCounter; // ID
} __attribute__((packed));

#endif // PRODOSERMEMORYMODEL_H
