/************************************************************************************
 * arch/arm/src/sama5/sam_dmac.h
 *
 *   Copyright (C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __ARCH_ARM_SRC_SAMA5_SAM_DMAC_H
#define __ARCH_ARM_SRC_SAMA5_SAM_DMAC_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>

#include "chip.h"

/************************************************************************************
 * Definitions
 ************************************************************************************/

/* Configuration ********************************************************************/

#ifndef CONFIG_DEBUG
#  undef CONFIG_DEBUG_DMA
#endif

/* DMA ******************************************************************************/

/* Flags used to characterize the DMA channel.  The naming convention is that one
 * side is the peripheral and the other is memory (however, the interface could still
 * be used if, for example, both sides were memory although the naming would be
 * awkward)
 */

/* Configurable properties of the channel */

#define DMACH_FLAG_BURST_LARGEST              0  /* Largest length AHB burst */
#define DMACH_FLAG_BURST_HALF                 1  /* Half FIFO size */
#define DMACH_FLAG_BURST_SINGLE               2  /* Single AHB access */

#define DMACH_FLAG_FIFOCFG_SHIFT              (0)       /* Bits 0-1: FIFO configuration */
#define DMACH_FLAG_FIFOCFG_MASK               (3 << DMACH_FLAG_FIFOCFG_SHIFT)
#  define DMACH_FLAG_FIFOCFG_LARGEST          (DMACH_FLAG_BURST_LARGEST << DMACH_FLAG_FIFOCFG_SHIFT)
#  define DMACH_FLAG_FIFOCFG_HALF             (DMACH_FLAG_BURST_HALF << DMACH_FLAG_FIFOCFG_SHIFT)
#  define DMACH_FLAG_FIFOCFG_SINGLE           (DMACH_FLAG_BURST_SINGLE << DMACH_FLAG_FIFOCFG_SHIFT)

/* Peripheral endpoint characteristics */

#define DMACH_FLAG_PERIPHPID_SHIFT            (2)       /* Bits 2-5: Peripheral PID */
#define DMACH_FLAG_PERIPHPID_MASK             (15 << DMACH_FLAG_PERIPHPID_SHIFT)
#define DMACH_FLAG_PERIPHH2SEL                (1 << 6)  /* Bits 6: HW handshaking */
#define DMACH_FLAG_PERIPHISPERIPH             (1 << 7)  /* Bits 7: 0=memory; 1=peripheral */
#define DMACH_FLAG_PERIPHWIDTH_SHIFT          (8)       /* Bits 8-9: Peripheral width */
#define DMACH_FLAG_PERIPHWIDTH_MASK           (3 << DMACH_FLAG_PERIPHWIDTH_SHIFT)
#  define DMACH_FLAG_PERIPHWIDTH_8BITS        (0 << DMACH_FLAG_PERIPHWIDTH_SHIFT) /* 8 bits */
#  define DMACH_FLAG_PERIPHWIDTH_16BITS       (1 << DMACH_FLAG_PERIPHWIDTH_SHIFT) /* 16 bits */
#  define DMACH_FLAG_PERIPHWIDTH_32BITS       (2 << DMACH_FLAG_PERIPHWIDTH_SHIFT) /* 32 bits */
#  define DMACH_FLAG_PERIPHWIDTH_64BITS       (3 << DMACH_FLAG_PERIPHWIDTH_SHIFT) /* 64 bits */
#define DMACH_FLAG_PERIPHINCREMENT            (1 << 10) /* Bit 10: Autoincrement peripheral address */
#define DMACH_FLAG_PERIPHCHUNKSIZE            (1 << 11) /* Bit 11: Peripheral chunk size */
#  define DMACH_FLAG_PERIPHCHUNKSIZE_1        (0)                        /* Peripheral chunksize = 1 */
#  define DMACH_FLAG_PERIPHCHUNKSIZE_4        DMACH_FLAG_PERIPHCHUNKSIZE /* Peripheral chunksize = 4 */

/* Memory endpoint characteristics */

#define DMACH_FLAG_MEMPID_SHIFT               (12)      /* Bits 12-15: Memory PID */
#define DMACH_FLAG_MEMPID_MASK                (15 << DMACH_FLAG_PERIPHPID_SHIFT)
#define DMACH_FLAG_MEMH2SEL                   (1 << 16) /* Bits 16: HW handshaking */
#define DMACH_FLAG_MEMISPERIPH                (1 << 17) /* Bits 17: 0=memory; 1=peripheral */
#define DMACH_FLAG_MEMWIDTH_SHIFT             (18)      /* Bits 18-19: Memory width */
#define DMACH_FLAG_MEMWIDTH_MASK              (3 << DMACH_FLAG_MEMWIDTH_SHIFT)
#  define DMACH_FLAG_MEMWIDTH_8BITS           (0 << DMACH_FLAG_MEMWIDTH_SHIFT) /* 8 bits */
#  define DMACH_FLAG_MEMWIDTH_16BITS          (1 << DMACH_FLAG_MEMWIDTH_SHIFT) /* 16 bits */
#  define DMACH_FLAG_MEMWIDTH_32BITS          (2 << DMACH_FLAG_MEMWIDTH_SHIFT) /* 32 bits */
#  define DMACH_FLAG_MEMWIDTH_64BITS          (3 << DMACH_FLAG_MEMWIDTH_SHIFT) /* 64 bits */
#define DMACH_FLAG_MEMINCREMENT               (1 << 20) /* Bit 20: Autoincrement memory address */
#define DMACH_FLAG_MEMCHUNKSIZE               (1 << 21) /* Bit 21: Memory chunk size */
#  define DMACH_FLAG_MEMCHUNKSIZE_1           (0)                     /* Memory chunksize = 1 */
#  define DMACH_FLAG_MEMCHUNKSIZE_4           DMACH_FLAG_MEMCHUNKSIZE /* Memory chunksize = 4 */

/************************************************************************************
 * Public Types
 ************************************************************************************/

typedef FAR void *DMA_HANDLE;
typedef void (*dma_callback_t)(DMA_HANDLE handle, void *arg, int result);

/* The following is used for sampling DMA registers when CONFIG DEBUG_DMA is selected */

#ifdef CONFIG_DEBUG_DMA
struct sam_dmaregs_s
{
  /* Global Registers */

  uint32_t gcfg;    /* DMAC Global Configuration Register */
  uint32_t en;      /* DMAC Enable Register */
  uint32_t sreq;    /* DMAC Software Single Request Register */
  uint32_t creq;    /* DMAC Software Chunk Transfer Request Register */
  uint32_t last;    /* DMAC Software Last Transfer Flag Register */
  uint32_t ebcimr;  /* DMAC Error Mask */
  uint32_t ebcisr;  /* DMAC Error Status */
  uint32_t chsr;    /* DMAC Channel Handler Status Register */
  uint32_t wpmr;    /* DMAC Write Protect Mode Register */
  uint32_t wpsr;    /* DMAC Write Protect Status Register */

  /* Channel Registers */

  uint32_t saddr;   /* DMAC Channel Source Address Register */
  uint32_t daddr;   /* DMAC Channel Destination Address Register */
  uint32_t dscr;    /* DMAC Channel Descriptor Address Register */
  uint32_t ctrla;   /* DMAC Channel Control A Register */
  uint32_t ctrlb;   /* DMAC Channel Control B Register */
  uint32_t cfg;     /* DMAC Channel Configuration Register */
  uint32_t spip;    /* DMAC Channel Source PinP Configuration Register */
  uint32_t dpip;    /* DMAC Channel Destination PinP Configuration Register */
};
#endif

/************************************************************************************
 * Inline Functions
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Public Data
 ************************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Function Prototypes
 ************************************************************************************/

/****************************************************************************
 * Name: sam_dmachannel
 *
 * Description:
 *   Allocate a DMA channel.  This function sets aside a DMA channel with
 *   the required FIFO size and flow control capabilities (determined by
 *   dma_flags) then  gives the caller exclusive access to the DMA channel.
 *
 *   The naming convention in all of the DMA interfaces is that one side is
 *   the 'peripheral' and the other is 'memory'.  Howerver, the interface
 *   could still be used if, for example, both sides were memory although
 *   the naming would be awkward.
 *
 * Returned Value:
 *   If a DMA channel if the required FIFO size is available, this function
 *   returns a non-NULL, void* DMA channel handle.  NULL is returned on any
 *   failure.
 *
 ****************************************************************************/

DMA_HANDLE sam_dmachannel(uint8_t dmacno, uint32_t dmach_flags);

/****************************************************************************
 * Name: sam_dmafree
 *
 * Description:
 *   Release a DMA channel.  NOTE:  The 'handle' used in this argument must
 *   NEVER be used again until sam_dmachannel() is called again to re-gain
 *   a valid handle.
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void sam_dmafree(DMA_HANDLE handle);

/****************************************************************************
 * Name: sam_dmatxsetup
 *
 * Description:
 *   Configure DMA for transmit of one buffer (memory to peripheral).  This
 *   function may be called multiple times to handle large and/or dis-
 *   continuous transfers.  Calls to sam_dmatxsetup() and sam_dmarxsetup()
 *   must not be intermixed on the same transfer, however.
 *
 ****************************************************************************/

int sam_dmatxsetup(DMA_HANDLE handle, uint32_t paddr, uint32_t maddr,
                   size_t nbytes);

/****************************************************************************
 * Name: sam_dmarxsetup
 *
 * Description:
 *   Configure DMA for receipt of one buffer (peripheral to memory).  This
 *   function may be called multiple times to handle large and/or dis-
 *   continuous transfers.  Calls to sam_dmatxsetup() and sam_dmarxsetup()
 *   must not be intermixed on the same transfer, however.
 *
 ****************************************************************************/

int sam_dmarxsetup(DMA_HANDLE handle, uint32_t paddr, uint32_t maddr,
                   size_t nbytes);

/****************************************************************************
 * Name: sam_dmastart
 *
 * Description:
 *   Start the DMA transfer
 *
 ****************************************************************************/

int sam_dmastart(DMA_HANDLE handle, dma_callback_t callback, void *arg);

/****************************************************************************
 * Name: sam_dmastop
 *
 * Description:
 *   Cancel the DMA.  After sam_dmastop() is called, the DMA channel is
 *   reset and sam_dmarx/txsetup() must be called before sam_dmastart() can be
 *   called again
 *
 ****************************************************************************/

void sam_dmastop(DMA_HANDLE handle);

/****************************************************************************
 * Name: sam_dmasample
 *
 * Description:
 *   Sample DMA register contents
 *
 ****************************************************************************/

#ifdef CONFIG_DEBUG_DMA
void sam_dmasample(DMA_HANDLE handle, struct sam_dmaregs_s *regs);
#else
#  define sam_dmasample(handle,regs)
#endif

/****************************************************************************
 * Name: sam_dmadump
 *
 * Description:
 *   Dump previously sampled DMA register contents
 *
 ****************************************************************************/

#ifdef CONFIG_DEBUG_DMA
void sam_dmadump(DMA_HANDLE handle, const struct sam_dmaregs_s *regs,
                 const char *msg);
#else
#  define sam_dmadump(handle,regs,msg)
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_SAMA5_SAM_DMAC_H */