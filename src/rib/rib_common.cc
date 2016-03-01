#include "rib_common.h"

frame_t get_frame(uint32_t sfn_sf) {
  uint16_t frame_mask = ((1<<12) - 1);
  return (sfn_sf & (frame_mask << 4)) >> 4;
}

subframe_t get_subframe(uint32_t sfn_sf) {
  uint16_t sf_mask = ((1<<4) - 1);
  return (sfn_sf & sf_mask);
}

std::pair<frame_t, subframe_t> get_frame_subframe(uint32_t sfn_sf) {
  uint32_t frame_mask =  ((1<<12) - 1);
  frame_t frame = (sfn_sf & (frame_mask << 4)) >> 4;
  uint32_t sf_mask = ((1<<4) - 1);
  subframe_t subframe =  (sfn_sf & sf_mask);
  return std::pair<frame_t, subframe_t>(frame, subframe);
}