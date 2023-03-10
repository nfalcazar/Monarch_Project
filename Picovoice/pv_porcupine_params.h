/*
    Copyright 2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/
#ifndef PV_PPN_PARAMS_H
#define PV_PPN_PARAMS_H

#include <stdint.h>

#ifdef __cplusplus

extern "C" {

#endif

// Wake-word = butterfly
static const uint8_t KEYWORD_ARRAY[520] __attribute__ ((aligned (16))) = {
        0xf8, 0x37, 0xf4, 0x6e, 0xa6, 0xd5, 0x56, 0xcc, 0x22, 0xbb, 0xfd, 0x20, 0x72, 0x9b, 0xe9, 0x46, 0x39, 0x78,
        0x42, 0x14, 0x18, 0xdd, 0x87, 0x59, 0x3a, 0xbe, 0x81, 0x4a, 0x04, 0x6f, 0x08, 0x01, 0x26, 0x2f, 0xcd, 0x1e,
        0x71, 0xa6, 0x6f, 0x2e, 0xad, 0xb9, 0x44, 0x5e, 0x2c, 0x5f, 0xda, 0x1d, 0x73, 0x59, 0xf0, 0x6c, 0x77, 0xec,
        0xa2, 0x63, 0x9a, 0xb5, 0x21, 0x31, 0x60, 0x72, 0xdc, 0x39, 0x60, 0x02, 0x4e, 0x75, 0x75, 0x1e, 0xee, 0x52,
        0x37, 0xed, 0x6a, 0xe4, 0x44, 0x30, 0x03, 0x10, 0x56, 0x59, 0xd5, 0x1f, 0x35, 0xfc, 0x27, 0x57, 0xf3, 0x44,
        0x17, 0x95, 0x35, 0x10, 0xed, 0x29, 0x90, 0x38, 0xc8, 0x2d, 0xd9, 0xf8, 0x2d, 0x67, 0xb9, 0x2e, 0xe6, 0x7a,
        0xb1, 0x18, 0xe6, 0x05, 0x72, 0xd6, 0xc8, 0xe5, 0x32, 0xe1, 0xd4, 0xae, 0xba, 0x94, 0x92, 0x86, 0x84, 0x77,
        0x81, 0x9a, 0xca, 0x9d, 0x10, 0x10, 0x52, 0x9e, 0x62, 0x99, 0x6b, 0x0b, 0x67, 0x23, 0x4b, 0xe3, 0x7e, 0xc0,
        0x11, 0xd6, 0x1e, 0xae, 0x4a, 0x72, 0x23, 0x33, 0x32, 0xe6, 0x5a, 0x1e, 0x84, 0xa6, 0x7b, 0xd8, 0x11, 0x39,
        0x82, 0xee, 0xe7, 0x99, 0x1d, 0x2e, 0x1a, 0x44, 0x4c, 0x3d, 0xdb, 0x35, 0x05, 0x6e, 0xb4, 0xad, 0x75, 0x9b,
        0xc7, 0x94, 0xff, 0x3a, 0xe6, 0xee, 0xe1, 0x53, 0xac, 0xf8, 0x06, 0x46, 0x2d, 0x42, 0x84, 0xf7, 0x10, 0x5e,
        0x07, 0x09, 0x5a, 0x09, 0xed, 0x20, 0xb8, 0x17, 0x60, 0xdd, 0x3f, 0x47, 0x31, 0xc1, 0x54, 0xc2, 0x6f, 0x28,
        0x42, 0x87, 0x3a, 0xf0, 0x15, 0x9d, 0x69, 0x0b, 0xde, 0x63, 0x50, 0xd0, 0x45, 0xf4, 0x4f, 0x7a, 0xfc, 0x2d,
        0xb9, 0x58, 0x19, 0x34, 0x45, 0x1a, 0x86, 0xb7, 0x6c, 0xec, 0x8d, 0x85, 0xab, 0xc2, 0xc2, 0x05, 0xcb, 0x45,
        0x00, 0x35, 0xf1, 0xfe, 0x9d, 0x99, 0x0f, 0x00, 0x70, 0x6f, 0xf7, 0xce, 0x9f, 0x59, 0x25, 0xf1, 0x9d, 0x06,
        0x31, 0x77, 0x3f, 0xc3, 0x83, 0x24, 0xef, 0xbe, 0x40, 0x0e, 0x5b, 0xc8, 0x4c, 0xcd, 0xd3, 0x28, 0x4f, 0x35,
        0xf2, 0x39, 0xf9, 0x36, 0x1d, 0x33, 0xec, 0x10, 0x6b, 0xa6, 0x31, 0xb5, 0x74, 0xe3, 0x26, 0x23, 0x39, 0x9a,
        0xc7, 0x3d, 0x9d, 0xbd, 0x30, 0xd4, 0xd2, 0xfc, 0x86, 0xb3, 0xa3, 0xf6, 0x13, 0xc3, 0x14, 0x03, 0x54, 0xe6,
        0x6c, 0x39, 0x18, 0x4a, 0x02, 0x0c, 0xff, 0x86, 0xd9, 0xea, 0x08, 0xc2, 0x72, 0x58, 0x43, 0xca, 0x93, 0xb1,
        0x1c, 0x69, 0x96, 0xa2, 0xa3, 0x00, 0x0d, 0xcc, 0xbb, 0x25, 0x49, 0x5f, 0xde, 0xb8, 0x0d, 0x12, 0xff, 0x61,
        0x15, 0x6e, 0xc0, 0x8b, 0x7c, 0xb2, 0x24, 0x14, 0xf9, 0x7a, 0xf2, 0xc3, 0x4c, 0xd3, 0xbe, 0xd2, 0x5f, 0xe6,
        0x98, 0x52, 0x65, 0xd9, 0x50, 0xbe, 0x17, 0x7e, 0xb1, 0xcf, 0x5e, 0x15, 0x37, 0x75, 0xcb, 0x25, 0xde, 0x40,
        0x7e, 0xd3, 0xaa, 0xd3, 0xaa, 0x35, 0x45, 0x08, 0x26, 0x9f, 0x2f, 0xec, 0x88, 0x4c, 0xfd, 0x1b, 0x76, 0x8f,
        0xc5, 0xa5, 0x50, 0x1b, 0x8e, 0x09, 0xff, 0xa1, 0xdb, 0x06, 0xfe, 0x5b, 0x29, 0x2f, 0x0f, 0x60, 0x27, 0x73,
        0x68, 0xc4, 0xec, 0xa7, 0xf1, 0x2d, 0xb8, 0xe8, 0x46, 0x74, 0x93, 0x3f, 0x55, 0x90, 0x5c, 0x19, 0x31, 0x2f,
        0xe9, 0xb6, 0x34, 0xa4, 0x2a, 0x8a, 0xf5, 0x65, 0xfc, 0xcc, 0xa8, 0xf8, 0xd6, 0x49, 0xd1, 0x95, 0x21, 0x3f,
        0x4b, 0x3a, 0x7f, 0x81, 0x86, 0xa4, 0xb5, 0x63, 0x98, 0x46, 0x46, 0x69, 0x99, 0xe6, 0x6d, 0x08, 0x1c, 0x9e,
        0xdd, 0x6b, 0x38, 0x3e, 0xce, 0x8f, 0x30, 0x81, 0x13, 0x0a, 0x36, 0xf0, 0x96, 0x14, 0x96, 0x17, 0x97, 0xc2,
        0x98, 0xfe, 0x71, 0x50, 0x72, 0x68, 0x20, 0xc7, 0x9b, 0x83, 0xab, 0x74, 0x2a, 0x8e, 0x9d, 0xc2
};

static const uint32_t KEYWORD_ARRAY_LENGTH = 520;

#ifdef __cplusplus

}

#endif // __cplusplus

#endif // PV_PPN_PARAMS_H