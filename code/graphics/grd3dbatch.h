#ifndef _GRD3DBATCH_H_
#define _GRD3DBATCH_H_


// Batch structure to be filled by process requesting batch
typedef struct {
	void (*state_set_func)();
	// For gr_set_bitmap
	int texture_id;
	// For gr_tcache_set
	int bitmap_type;

	// For gr_d3d_set_state
	int filter_type;
	int alpha_blend_type;
	int zbuffer_type;

	int is_set;

} BatchInfo;

bool d3d_batch_init();
void d3d_batch_deinit();

int d3d_create_batch(int num_verts, int vert_type, int ptype);
void d3d_destory_batch(int batch_id);
void *d3d_batch_lock_vbuffer(int batch_id, int num_to_lock, BatchInfo &batch_info);
void d3d_batch_unlock_vbuffer(int batch_id);
bool d3d_batch_draw_vbuffer(int batch_id);
void d3d_batch_end_frame();
void d3d_batch_string(int sx, int sy, char *s, int bw, int bh, float u_scale, float v_scale, uint color);

#endif
