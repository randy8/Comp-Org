// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// or any other unauthorized source, either modified or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from another source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// Randy Liang <randy8>

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "bytes.h"

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "bytes.h"

void bytes_init(bytes_t * const bytes) {
	bytes->data = NULL;
	bytes->usage = 0;
	bytes->dim = DEFAULT_SIZE;
}

void bytes_free(bytes_t * const bytes) {
	free(bytes->data);
	bytes->data = NULL;
}

void bytes_fprintf(FILE * out, const bytes_t * const bytes)
{
	const uint8_t *data = (bytes->data == NULL) ? bytes->dflt : bytes->data;

	fprintf(out, "          ");

	for (size_t b = 0; b < BYTES_PER_LINE; b++)
	{
		fprintf(out, "%02zx ", b);
	}
	fprintf(out, "\n");

	fprintf(out, "         ");
	fprintf(out, " -----------------------------------------------");
	fprintf(out, "\n");

 	for (size_t x = 0; x < bytes->usage; x += 16)
	{
		size_t min = (bytes->usage  >= x + BYTES_PER_LINE)
				? x + BYTES_PER_LINE : bytes->usage;

		fprintf(out, "%08zx  ", x);

		for (size_t y = x; y < min; y++)
		{
			fprintf(out, "%02"PRIx8" ", data[y]);
		}
		fprintf(out, "\n");
	}

	fprintf(out, "         ");
	fprintf(out, " -----------------------------------------------");
	fprintf(out, "\n");
	fprintf(out, "\n");

}

bool bytes_empty(const bytes_t * const bytes) {
	return bytes->usage == 0;
}

uint8_t * bytes_data(const bytes_t * const bytes) {
	uint8_t * bd = (bytes->data == NULL) ? bytes->dflt : bytes->data;
	return bd;
}

size_t bytes_usage(const bytes_t * const bytes) {
	return bytes->usage;
}

bool bytes_set(bytes_t * const bytes, size_t index, uint8_t val) {
	if (index < bytes->usage) {
		uint8_t * ptr = bytes_data(bytes);
		ptr += index;
		*ptr = val;
		return true;
	} 
	else {
		return false;
	}
}

bool bytes_get(const bytes_t * const bytes, size_t index,
		width_t width, endian_t order, uint64_t * const result) {
	uint8_t newWidth = 1 << width;

	if (index + newWidth > bytes->usage) {
		return false;
	}
	if (bytes->data != NULL) {
		uint8_t* data = bytes->data;
		data += index;
		uint64_t accumulator = 0;

		if (newWidth == 1) {
			*result = *data;
			return true;
		}
		if (order == 0) { 
			data += newWidth - 1;
			for (int i = newWidth; i > 0; i--) {
				uint64_t multiplier = 1;
				for (uint64_t j = 0; j < newWidth - i; j++) {
					multiplier *= 256;
				}
				accumulator += *data * multiplier;
				data--;
			}
		} 
		else { 
			for (uint8_t i = 0; i < newWidth; i++) {
				uint64_t multiplier = 1;
				for (uint64_t j = 0; j < i; j++) {
					multiplier *= 256;
				}
				accumulator += *(data) * multiplier;
				data++;
			}
		}
		*result = accumulator;
		return true;
	} 
	else { 
		uint64_t accumulator = 0;
		if (order == 0) { 
			for (int i = index + newWidth; i > index; i--) {
				uint64_t multiplier = 1;
				for (uint64_t j = 0; j < i - index - 1; j++) {
					multiplier *= 256;
				}
				accumulator += bytes->dflt[i - 1] * multiplier;
			}
		} 
		else {
			for (uint8_t i = index; i < index + newWidth; i++) {
				uint64_t multiplier = 1;
				for (uint8_t j = 0; j < i - index; j++) {
					multiplier *= 256;
				}
				accumulator += bytes->dflt[i] * multiplier;
			}
		}
		*result = accumulator;
		return true;
	}
}

bool bytes_insert(bytes_t * bytes, size_t index,
			const uint8_t * buf, size_t len){
	if (bytes->usage + len >= DEFAULT_SIZE && bytes->data == NULL) { 
		if (bytes->data == NULL) { 
			bytes->data = (uint8_t *) calloc(bytes->dim * 2, sizeof(uint8_t));
			for (uint8_t i = 0; i < bytes->usage; i++) { 
				*(bytes->data + i) = bytes->dflt[i];
			}
		}
		if (index <= bytes->usage - 1 && bytes->usage != 0) {
			uint8_t* ptr = bytes->data;
			for (uint8_t i = bytes->usage - 1; i >= index; i--) {
				*(ptr + i + len) = *(ptr + i);
			}
			for (uint8_t j = index; j < index + len; j++) {
				*(ptr + j) = *buf;
				buf++;
			}
		} 
		else {
			for (uint8_t i = 0; i <= len; i++) {
				*(bytes->data + i + bytes->usage) = *(buf + i);
			}
		}
		bytes->usage += len;
		bytes->dim *= 2;
		return true;
	} 
	else if (bytes->usage + len > bytes->dim && bytes->data != NULL) {
		uint8_t* next = (uint8_t *) calloc(bytes->dim * 2, sizeof(uint8_t));
		uint8_t* ptr = bytes->data;
		for (uint8_t i = 0; i < bytes->usage; i++) {
			*(next + i) = *(ptr + i);
		}
		free(bytes->data);
		bytes->data = (uint8_t *) calloc(bytes->dim * 2, sizeof(uint8_t));
		for (uint8_t i = 0; i < bytes->dim * 2; i++) {
			*(bytes->data + i) = *(next + i);
		}
		free(next);

		if (index <= bytes->usage - 1 && bytes->usage != 0) {
			uint8_t* ptr = bytes->data;
			for (uint8_t i = bytes->usage - 1; i >= index; i--) {
				*(ptr + i + len) = *(ptr + i);
			}
			for (uint8_t j = index; j < index + len; j++) {
				*(ptr + j) = *buf;
				buf++;
			}
		} 
		else {
			uint8_t* ptr = bytes->data;
			ptr += bytes->usage;
			for (uint8_t i = 0; i < len; i++) {
				*(ptr + i) = *(buf + i);
			}
		}
		bytes->usage += len;
		bytes->dim *= 2;
		return true;
	} 
	else if (bytes->usage + len <= bytes->dim && bytes->data != NULL) {
		if (index <= bytes->usage - 1 && bytes->usage != 0) {
			uint8_t* ptr = bytes->data;
			for (uint8_t i = bytes->usage - 1; i >= index; i--) {
				*(ptr + i + len) = *(ptr + i);
			}
			for (uint8_t j = index; j < index + len; j++) {
				*(ptr + j) = *buf;
				buf++;
			}
		} 
		else {
			uint8_t* ptr = bytes->data;
			ptr += bytes->usage;
			for (uint8_t i = 0; i < len; i++) {
				*(ptr + i) = *(buf + i);
			}
		}
		bytes->usage += len;
		return true;
	} 
	else {
		if (index <= bytes->usage - 1 && bytes->usage != 0) {
			for (int i = bytes->usage - 1; i >= index && i >= 0; i--) { 
				bytes->dflt[i + len] = bytes->dflt[i];
			}
			for (uint8_t j = index; j < index + len; j++) {
				bytes->dflt[j] = *buf;
				buf++;
			}
			bytes->usage += len;
			return true;
		} 
		else {
			for (uint8_t i = 0; i <= len; i++) {
				bytes->dflt[i + bytes->usage] = *(buf + i);
			}
			bytes->usage += len;
			return true;
		}
	}
	return false;
}

bool bytes_erase(bytes_t * const bytes, size_t index, size_t len) {
	if (index >= bytes->usage ) {
		return false;
	}
	uint8_t erase_len;
	if (index + len > bytes->usage) {
		erase_len = bytes->usage - index;
	} 
	else {
		erase_len = len;
	}
	if (bytes->data == NULL) {
		for (uint8_t i = index; i < index + erase_len; i++) {
			bytes->dflt[i] = 0;
		}
	} 
	else {
		uint8_t* newptr = (uint8_t*) calloc(bytes->usage, sizeof(uint8_t));
		for (uint8_t first = 0; first < index; first++) { 
			*(newptr + first) = *(bytes->data + first);
		}
		uint8_t nextctr = index;
		for (uint8_t next = index + erase_len; next < bytes->usage; next++) { 
			*(newptr + nextctr) = *(bytes->data + next);
			nextctr++;
		}
		free(bytes->data);
		bytes->data = (uint8_t* ) malloc(bytes->dim * sizeof(uint8_t));
		for (uint8_t i = 0; i < bytes->usage - erase_len; i++) { 
			*(bytes->data + i) = *(newptr + i);
		}
		bytes->usage -= erase_len;
		free(newptr);
	}
	return true;
}

uint8_t * bytes_range(const bytes_t * const bytes, range_t *range) {
	if (range->step > 0 && range->start >= range->stop || range->step < 0 && range->start <= range->stop) {
		return NULL;
	} 
	uint8_t * ptr;
	if (bytes->data != NULL) {
		ptr = bytes->data;
		ptr += range->start;
		range->start += range->step;
		return ptr;
	}
	else {
		ptr = bytes->dflt;
		ptr += range->start;
		range->start += range->step;
		return ptr;
	} 
}

bool bytes_copy(bytes_t * const dest, const bytes_t * const src) {
	if (src->data == NULL && dest->data == NULL) {
		for (uint8_t i = 0; i < DEFAULT_SIZE; i++) {
			dest->dflt[i] = src->dflt[i];
		}
		dest->usage = src->usage;
		return true;
	} 
	else if (src->data == NULL && dest->data != NULL) {
		free(dest->data);
		dest->data = (uint8_t* ) malloc(dest->dim * sizeof(uint8_t));
		uint8_t* ptr = dest->data;
		for (uint8_t i = 0; i < src->usage; i++) {
			*ptr = src->dflt[i];
			ptr++;
		}
		dest->usage = src->usage;
		dest->dim = src->dim;
		return true;
	}
	else if (src->data != NULL && dest->data == NULL) {
		dest->data = (uint8_t* ) malloc(src->dim * sizeof(uint8_t));
		uint8_t* dptr = dest->data;
		uint8_t* sptr = src->data;
		for (uint8_t i = 0; i < src->usage; i++) {
			*(dptr + i) = *(sptr + i);
		}
		dest->usage = src->usage;
		dest->dim = src->dim;
		return true;
	} 
	return false;
}