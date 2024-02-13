#include <cart.h>

typedef struct {
    char filename[1024];
    u32 rom_size;
    u8 *rom_data;
    rom_header *header;
} cart_context;

static cart_context ctx;

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

char *get_new_lic_code() {
  // ASCII 00 => 0x3030, 01 => 0X3031, ...etc
  switch (ctx.header->new_lic_code) {
  case (0x3030):
    return "None";
  case (0x3031):
    return "Nintendo R&D1";
  case (0x3038):
    return "Capcom";
  case (0x3133):
    return "Electronic Arts";
  case (0x3138):
    return "Hudson Soft";
  case (0x3139):
    return "b-ai";
  case (0x3230):
    return "kss";
  case (0x3232):
    return "pow";
  case (0x3234):
    return "PCM Complete";
  case (0x3235):
    return "san-x";
  case (0x3238):
    return "Kemco Japan";
  case (0x3239):
    return "seta";
  case (0x3330):
    return "Viacom";
  case (0x3331):
    return "Nintendo";
  case (0x3332):
    return "Bandai";
  case (0x3333):
    return "Ocean/Acclaim";
  case (0x3334):
    return "Konami";
  case (0x3335):
    return "Hector";
  case (0x3337):
    return "Taito";
  case (0x3338):
    return "Hudson";
  case (0x3339):
    return "Banpresto";
  case (0x3431):
    return "Ubi Soft";
  case (0x3432):
    return "Atlus";
  case (0x3434):
    return "Malibu";
  case (0x3436):
    return "angel";
  case (0x3437):
    return "Bullet-Proof";
  case (0x3439):
    return "irem";
  case (0x3530):
    return "Absolute";
  case (0x3531):
    return "Acclaim";
  case (0x3532):
    return "Activision";
  case (0x3533):
    return "American sammy";
  case (0x3534):
    return "Konami";
  case (0x3535):
    return "Hi tech entertainment";
  case (0x3536):
    return "LJN";
  case (0x3537):
    return "Matchbox";
  case (0x3538):
    return "Mattel";
  case (0x3539):
    return "Milton Bradley";
  case (0x3630):
    return "Titus";
  case (0x3631):
    return "Virgin";
  case (0x3634):
    return "LucasArts";
  case (0x3637):
    return "Ocean";
  case (0x3639):
    return "Electronic Arts";
  case (0x3730):
    return "Infogrames";
  case (0x3731):
    return "Interplay";
  case (0x3732):
    return "Broderbund";
  case (0x3733):
    return "sculptured";
  case (0x3735):
    return "sci";
  case (0x3738):
    return "THQ";
  case (0x3739):
    return "Accolade";
  case (0x3830):
    return "misawa";
  case (0x3833):
    return "lozc";
  case (0x3836):
    return "Tokuma Shoten Intermedia";
  case (0x3837):
    return "Tsukuda Original";
  case (0x3931):
    return "Chunsoft";
  case (0x3932):
    return "Video system";
  case (0x3933):
    return "Ocean/Acclaim";
  case (0x3935):
    return "Varie";
  case (0x3936):
    return "Yonezawa/s’pal";
  case (0x3937):
    return "Kaneko";
  case (0x3939):
    return "Pack in soft";
  case (0x3948):
    return "Bottom up";
  case (0x4134):
   return "Konami (Yu-Gi-Oh!)";
  default:
    return "UNKNOWN";
      }
}
static const char *LIC_CODE[0xA5] = {
  // The old lic_code is HEX based.
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
    return get_new_lic_code();
}

const char *cart_type_name() {
    if (ctx.header->type <= 0x22) {
        return ROM_TYPES[ctx.header->type];
    }

    return "UNKNOWN";
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

    // new_lic_code is a two letters ASCII code c.f. (https://gbdev.io/pandocs/The_Cartridge_Header.html#01440145--new-licensee-code)
    ctx.header->new_lic_code = (ctx.rom_data[0x144]<<8) | (ctx.rom_data[0x145]);

    printf("Cartridge Loaded:\n");
    printf("\t Title    : %s\n", ctx.header->title);
    printf("\t Type     : %2.2X (%s)\n", ctx.header->type, cart_type_name());
    printf("\t ROM Size : %d KB\n", 32 << ctx.header->rom_size);
    printf("\t RAM Size : %2.2X\n", ctx.header->ram_size);
    printf("\t LIC Code : %2.2X (%s)\n", ctx.header->lic_code, cart_lic_name());
    printf("\t ROM Vers : %2.2X\n", ctx.header->version);

    u16 x = 0;
    for (u16 i=0x0134; i<=0x014C; i++) {
        x = x - ctx.rom_data[i] - 1;
    }

    printf("\t Checksum : %2.2X (%s)\n", ctx.header->checksum, (x & 0xFF) ? "PASSED" : "FAILED");

    return true;
}
