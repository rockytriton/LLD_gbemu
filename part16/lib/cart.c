#include <cart.h>
#include <string.h>

typedef struct {
    char filename[1024];
    u32 rom_size;
    u8 *rom_data;
    rom_header *header;

    //mbc1 related data
    bool ram_enabled;
    bool ram_banking;

    u8 *rom_bank_x;
    u8 banking_mode;

    u8 rom_bank_value;
    u8 ram_bank_value;

    u8 *ram_bank; //current selected ram bank
    u8 *ram_banks[16]; //all ram banks

    //for battery
    bool battery; //has battery
    bool need_save; //should save battery backup.
} cart_context;

static cart_context ctx;

bool cart_need_save() {
    return ctx.need_save;
}

bool cart_mbc1() {
    return BETWEEN(ctx.header->type, 1, 3);
}

bool cart_battery() {
    //mbc1 only for now...
    return ctx.header->type == 3;
}

static const char *ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char *LIC_CODE[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
};

const char *cart_lic_name() {
    if (ctx.header->new_lic_code <= 0xA4) {
        return LIC_CODE[ctx.header->lic_code];
    }

    return "UNKNOWN";
}

const char *cart_type_name() {
    if (ctx.header->type <= 0x22) {
        return ROM_TYPES[ctx.header->type];
    }

    return "UNKNOWN";
}

void cart_setup_banking() {
    for (int i=0; i<16; i++) {
        ctx.ram_banks[i] = 0;

        if ((ctx.header->ram_size == 2 && i == 0) ||
            (ctx.header->ram_size == 3 && i < 4) || 
            (ctx.header->ram_size == 4 && i < 16) || 
            (ctx.header->ram_size == 5 && i < 8)) {
            ctx.ram_banks[i] = malloc(0x2000);
            memset(ctx.ram_banks[i], 0, 0x2000);
        }
    }

    ctx.ram_bank = ctx.ram_banks[0];
    ctx.rom_bank_x = ctx.rom_data + 0x4000; //rom bank 1
}

bool cart_load(char *cart) {
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart);

    FILE *fp = fopen(cart, "r");

    if (!fp) {
        printf("Failed to open: %s\n", cart);
        return false;
    }

    printf("Opened: %s\n", ctx.filename);

    fseek(fp, 0, SEEK_END);
    ctx.rom_size = ftell(fp);

    rewind(fp);

    ctx.rom_data = malloc(ctx.rom_size);
    fread(ctx.rom_data, ctx.rom_size, 1, fp);
    fclose(fp);

    ctx.header = (rom_header *)(ctx.rom_data + 0x100);
    ctx.header->title[15] = 0;
    ctx.battery = cart_battery();
    ctx.need_save = false;

    printf("Cartridge Loaded:\n");
    printf("\t Title    : %s\n", ctx.header->title);
    printf("\t Type     : %2.2X (%s)\n", ctx.header->type, cart_type_name());
    printf("\t ROM Size : %d KB\n", 32 << ctx.header->rom_size);
    printf("\t RAM Size : %2.2X\n", ctx.header->ram_size);
    printf("\t LIC Code : %2.2X (%s)\n", ctx.header->lic_code, cart_lic_name());
    printf("\t ROM Vers : %2.2X\n", ctx.header->version);

    cart_setup_banking();

    u16 x = 0;
    for (u16 i=0x0134; i<=0x014C; i++) {
        x = x - ctx.rom_data[i] - 1;
    }

    printf("\t Checksum : %2.2X (%s)\n", ctx.header->checksum, (x & 0xFF) ? "PASSED" : "FAILED");

    if (ctx.battery) {
        cart_battery_load();
    }

    return true;
}

void cart_battery_load() {
    if (!ctx.ram_bank) {
        return;
    }

    char fn[1048];
    sprintf(fn, "%s.battery", ctx.filename);
    FILE *fp = fopen(fn, "rb");

    if (!fp) {
        fprintf(stderr, "FAILED TO OPEN: %s\n", fn);
        return;
    }

    fread(ctx.ram_bank, 0x2000, 1, fp);
    fclose(fp);
}

void cart_battery_save() {
    if (!ctx.ram_bank) {
        return;
    }

    char fn[1048];
    sprintf(fn, "%s.battery", ctx.filename);
    FILE *fp = fopen(fn, "wb");

    if (!fp) {
        fprintf(stderr, "FAILED TO OPEN: %s\n", fn);
        return;
    }

    fwrite(ctx.ram_bank, 0x2000, 1, fp);
    fclose(fp);
}

u8 cart_read(u16 address) {
    if (!cart_mbc1() || address < 0x4000) {
        return ctx.rom_data[address];
    }

    if ((address & 0xE000) == 0xA000) {
        if (!ctx.ram_enabled) {
            return 0xFF;
        }

        if (!ctx.ram_bank) {
            return 0xFF;
        }

        return ctx.ram_bank[address - 0xA000];
    }

    return ctx.rom_bank_x[address - 0x4000];
}

void cart_write(u16 address, u8 value) {
    if (!cart_mbc1()) {
        return;
    }

    if (address < 0x2000) {
        ctx.ram_enabled = ((value & 0xF) == 0xA);
    }

    if ((address & 0xE000) == 0x2000) {
        //rom bank number
        if (value == 0) {
            value = 1;
        }

        value &= 0b11111;

        ctx.rom_bank_value = value;
        ctx.rom_bank_x = ctx.rom_data + (0x4000 * ctx.rom_bank_value);
    }

    if ((address & 0xE000) == 0x4000) {
        //ram bank number
        ctx.ram_bank_value = value & 0b11;

        if (ctx.ram_banking) {
            if (cart_need_save()) {
                cart_battery_save();
            }

            ctx.ram_bank = ctx.ram_banks[ctx.ram_bank_value];
        }
    }

    if ((address & 0xE000) == 0x6000) {
        //banking mode select
        ctx.banking_mode = value & 1;

        ctx.ram_banking = ctx.banking_mode;

        if (ctx.ram_banking) {
            if (cart_need_save()) {
                cart_battery_save();
            }
            
            ctx.ram_bank = ctx.ram_banks[ctx.ram_bank_value];
        }
    }

    if ((address & 0xE000) == 0xA000) {
        if (!ctx.ram_enabled) {
            return;
        }

        if (!ctx.ram_bank) {
            return;
        }

        ctx.ram_bank[address - 0xA000] = value;

        if (ctx.battery) {
            ctx.need_save = true;
        }
    }
}

