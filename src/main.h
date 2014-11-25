#ifndef _MAIN_H_
#define _MAIN_H_

#include <asf.h>

#define stringify(x)			#x
#define xstringify(s) stringify(s)
#define A 0
#define B 1

typedef enum chan_mode{
	DISABLED = 0,
	SVMI = 1,
	SIMV = 2,
} chan_mode;


typedef struct IN_packet {
	uint16_t data_a_v[256];
	uint16_t data_a_i[256];
	uint16_t data_b_v[256];
	uint16_t data_b_i[256];
} IN_packet;

typedef struct OUT_packet{
	uint16_t data_a[256];
	uint16_t data_b[256];
} OUT_packet;

typedef struct rgb {
    uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb;

typedef struct ch_params {
	uint16_t i0_dac;
	uint16_t v0_adc;
	uint16_t i0_adc;
	uint8_t p1_simv;
	uint8_t p2_simv;
} ch_params;

IN_packet packets_in[2];
OUT_packet packets_out[2];



uint8_t serial_number[USB_DEVICE_GET_SERIAL_NAME_LENGTH];
volatile uint32_t slot_offset;
volatile uint32_t packet_index_in;
volatile uint32_t packet_index_out;
volatile uint32_t packet_index_send_in;
volatile uint32_t packet_index_send_out;
volatile bool send_in;
volatile bool send_out;
volatile bool sending_in;
volatile bool sending_out;
volatile bool sent_in;
volatile bool sent_out;
volatile bool channel_a;
volatile bool reset;
volatile bool main_b_vendor_enable;

uint8_t ret_data[16];

bool main_vendor_enable(void);

void main_vendor_disable(void);

void main_sof_action(void);

void main_suspend_action(void);

void h_to_rgb(uint8_t , rgb * c);

void main_resume_action(void);

bool main_setup_handle(void);

void init_build_usb_serial_number(void);

void init_hardware(void);
void config_hardware(void);

void write_ad5122(uint32_t ch, uint8_t r1, uint8_t r2);
void write_adm1177(uint8_t v);
void write_ad5663(uint8_t conf, uint16_t data);
void read_adm1177(uint8_t b[], uint8_t c);
void set_mode(uint32_t chan, chan_mode m);

void main_vendor_bulk_out_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep);
void main_vendor_bulk_in_received(udd_ep_status_t status, iram_size_t nb_transfered, udd_ep_id_t ep);

#endif
