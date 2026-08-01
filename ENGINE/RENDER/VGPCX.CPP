#include "engine\render\vgpcx.h"
#include "engine\defs.h"

#include "engine\types\vgstring.h"
#include "engine\render\pxlbuff.h"

#include <mem.h>
#include <stdio.h>

PixelBuffer* VGPCX::LoadPCX(const char* _filename) {
	FILE* file = fopen(_filename, "rb");
  if (file == null) {
  	// TODO: LOGGER
		return null;
  }

	byte_t header[128];
  fread(header, 1, 128, file);

  if (header[0] != 0x0A) { // pcx identifier
  	fclose(file);
    return null;
  }

  int16_t xMin = header[4] | header[5] << 8;
  int16_t yMin = header[6] | header[7] << 8;

  int16_t xMax = header[8] | header[9] << 8;
  int16_t yMax = header[10] | header[11] << 8;

  int width = (xMax - xMin) + 1;
  int height = (yMax - yMin) + 1;

  PixelBuffer* pbuff = new PixelBuffer(width, height);
	byte_t far* pixels = pbuff->Pixels();

  uint32_t remaining((uint32_t)width * height);
  uint32_t offset(0);

	while (remaining > 0) {
		byte_t byte;
    fread(&byte, 1, 1, file);

    if ((byte & 0xC0) == 0xC0) { // RLE
			int count = byte & 0x3F;
      fread(&byte, 1, 1, file);

      count = vmin(count, remaining);
      _fmemset(pixels + offset, byte, count);
      offset += count;
      remaining -= count;
      continue;
    }

    pixels[offset++] = byte;
    remaining--;
  };

  // palette time
  byte_t palette[768]; // todo: store palette on PixelBuffer OR
                           //       palette manager type thing.

  fseek(file, -769, SEEK_END);
  byte_t marker = 0;
  fread(&marker, 1, 1, file);
  if (marker == 0x0C) {
  	fread(&palette, 1, 768, file);
  }

  fclose(file);
  return pbuff;
}