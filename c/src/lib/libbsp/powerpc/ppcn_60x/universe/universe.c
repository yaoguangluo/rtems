/*
 *  COPYRIGHT (c) 1998 by Radstone Technology
 *
 *
 * THIS FILE IS PROVIDED TO YOU, THE USER, "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK
 * AS TO THE QUALITY AND PERFORMANCE OF ALL CODE IN THIS FILE IS WITH YOU.
 *
 * You are hereby granted permission to use, copy, modify, and distribute
 * this file, provided that this notice, plus the above copyright notice
 * and disclaimer, appears in all copies. Radstone Technology will provide
 * no support for this code.
 *
 *  COPYRIGHT (c) 1989, 1990, 1991, 1992, 1993, 1994, 1997.
 *  On-Line Applications Research Corporation (OAR).
 *
 * $Id$
 */

#include <rtems.h>
#include <assert.h>
#include <stdio.h>

#include <bsp.h>
#include <pci.h>

/********************************************************************
 ********************************************************************
 *********                                                  *********
 *********                  Prototypes                      *********
 *********                                                  *********
 ********************************************************************
 ********************************************************************/

typedef struct {
  uint32_t         PCI_ID;                 /* Offset 0x0000 */
  uint32_t         PCI_CSR;                /* Offset 0x0004 */
  uint32_t         PCI_CLASS;              /* Offset 0x0008 */
  uint32_t         PCI_MISC0;              /* Offset 0x000C */
  uint32_t         PCI_BS;                 /* Offset 0x0010 */
  uint32_t         Buf_Offset_0x0014[ 0x0A ]; /* Offset 0x0014 */
  uint32_t         PCI_MISC1;              /* Offset 0x003C */
  uint32_t         Buf_Offset_0x0040[ 0x30 ]; /* Offset 0x0040 */
  uint32_t         LSI0_CTL;               /* Offset 0x0100 */
  uint32_t         LSI0_BS;                /* Offset 0x0104 */
  uint32_t         LSI0_BD;                /* Offset 0x0108 */
  uint32_t         LSI0_TO;                /* Offset 0x010C */
  uint32_t         Buf_Offset_0x0110;         /* Offset 0x0110 */
  uint32_t         LSI1_CTL;               /* Offset 0x0114 */
  uint32_t         LSI1_BS;                /* Offset 0x0118 */
  uint32_t         LSI1_BD;                /* Offset 0x011C */
  uint32_t         LSI1_TO;                /* Offset 0x0120 */
  uint32_t         Buf_Offset_0x0124;         /* Offset 0x0124 */
  uint32_t         LSI2_CTL;               /* Offset 0x0128 */
  uint32_t         LSI2_BS;                /* Offset 0x012C */
  uint32_t         LSI2_BD;                /* Offset 0x0130 */
  uint32_t         LSI2_TO;                /* Offset 0x0134 */
  uint32_t         Buf_Offset_0x0138;         /* Offset 0x0138 */
  uint32_t         LSI3_CTL;               /* Offset 0x013C */
  uint32_t         LSI3_BS;                /* Offset 0x0140 */
  uint32_t         LSI3_BD;                /* Offset 0x0144 */
  uint32_t         LSI3_TO;                /* Offset 0x0148 */
  uint32_t         Buf_Offset_0x014C[ 0x09 ]; /* Offset 0x014C */
  uint32_t         SCYC_CTL;               /* Offset 0x0170 */
  uint32_t         SCYC_ADDR;              /* Offset 0x0174 */
  uint32_t         SCYC_EN;                /* Offset 0x0178 */
  uint32_t         SCYC_CMP;               /* Offset 0x017C */
  uint32_t         SCYC_SWP;               /* Offset 0x0180 */
  uint32_t         LMISC;                  /* Offset 0x0184 */
  uint32_t         SLSI;                   /* Offset 0x0188 */
  uint32_t         L_CMDERR;               /* Offset 0x018C */
  uint32_t         LAERR;                  /* Offset 0x0190 */
  uint32_t         Buf_Offset_0x0194[ 0x1B ]; /* Offset 0x0194 */
  uint32_t         DCTL;                   /* Offset 0x0200 */
  uint32_t         DTBC;                   /* Offset 0x0204 */
  uint32_t         DLA;                    /* Offset 0x0208 */
  uint32_t         Buf_Offset_0x020C;         /* Offset 0x020C */
  uint32_t         DVA;                    /* Offset 0x0210 */
  uint32_t         Buf_Offset_0x0214;         /* Offset 0x0214 */
  uint32_t         DCPP;                   /* Offset 0x0218 */
  uint32_t         Buf_Offset_0x021C;         /* Offset 0x021C */
  uint32_t         DGCS;                   /* Offset 0x0220 */
  uint32_t         D_LLUE;                 /* Offset 0x0224 */
  uint32_t         Buf_Offset_0x0228[ 0x36 ]; /* Offset 0x0228 */
  uint32_t         LINT_EN;                /* Offset 0x0300 */
  uint32_t         LINT_STAT;              /* Offset 0x0304 */
  uint32_t         LINT_MAP0;              /* Offset 0x0308 */
  uint32_t         LINT_MAP1;              /* Offset 0x030C */
  uint32_t         VINT_EN;                /* Offset 0x0310 */
  uint32_t         VINT_STAT;              /* Offset 0x0314 */
  uint32_t         VINT_MAP0;              /* Offset 0x0318 */
  uint32_t         VINT_MAP1;              /* Offset 0x031C */
  uint32_t         STATID;                 /* Offset 0x0320 */
  uint32_t         V1_STATID;              /* Offset 0x0324 */
  uint32_t         V2_STATID;              /* Offset 0x0328 */
  uint32_t         V3_STATID;              /* Offset 0x032C */
  uint32_t         V4_STATID;              /* Offset 0x0330 */
  uint32_t         V5_STATID;              /* Offset 0x0334 */
  uint32_t         V6_STATID;              /* Offset 0x0338 */
  uint32_t         V7_STATID;              /* Offset 0x033C */
  uint32_t         Buf_Offset_0x0340[ 0x30 ]; /* Offset 0x0340 */
  uint32_t         MAST_CTL;               /* Offset 0x0400 */
  uint32_t         MISC_CTL;               /* Offset 0x0404 */
  uint32_t         MISC_STAT;              /* Offset 0x0408 */
  uint32_t         USER_AM;                /* Offset 0x040C */
  uint32_t         Buf_Offset_0x0410[ 0x2bc ];/* Offset 0x0410 */
  uint32_t         VSI0_CTL;               /* Offset 0x0F00 */
  uint32_t         VSI0_BS;                /* Offset 0x0F04 */
  uint32_t         VSI0_BD;                /* Offset 0x0F08 */
  uint32_t         VSI0_TO;                /* Offset 0x0F0C */
  uint32_t         Buf_Offset_0x0f10;         /* Offset 0x0F10 */
  uint32_t         VSI1_CTL;               /* Offset 0x0F14 */
  uint32_t         VSI1_BS;                /* Offset 0x0F18 */
  uint32_t         VSI1_BD;                /* Offset 0x0F1C */
  uint32_t         VSI1_TO;                /* Offset 0x0F20 */
  uint32_t         Buf_Offset_0x0F24;         /* Offset 0x0F24 */
  uint32_t         VSI2_CTL;               /* Offset 0x0F28 */
  uint32_t         VSI2_BS;                /* Offset 0x0F2C */
  uint32_t         VSI2_BD;                /* Offset 0x0F30 */
  uint32_t         VSI2_TO;                /* Offset 0x0F34 */
  uint32_t         Buf_Offset_0x0F38;         /* Offset 0x0F38 */
  uint32_t         VSI3_CTL;               /* Offset 0x0F3C */
  uint32_t         VSI3_BS;                /* Offset 0x0F40 */
  uint32_t         VSI3_BD;                /* Offset 0x0F44 */
  uint32_t         VSI3_TO;                /* Offset 0x0F48 */
  uint32_t         Buf_Offset_0x0F4C[ 0x9 ];  /* Offset 0x0F4C */
  uint32_t         VRAI_CTL;               /* Offset 0x0F70 */
  uint32_t         VRAI_BS;                /* Offset 0x0F74 */
  uint32_t         Buf_Offset_0x0F78[ 0x2 ];  /* Offset 0x0F78 */
  uint32_t         VCSR_CTL;               /* Offset 0x0F80 */
  uint32_t         VCSR_TO;                /* Offset 0x0F84 */
  uint32_t         V_AMERR;                /* Offset 0x0F88 */
  uint32_t         VAERR;                  /* Offset 0x0F8C */
  uint32_t         Buf_Offset_0x0F90[ 0x19 ]; /* Offset 0x0F90 */
  uint32_t         VCSR_CLR;               /* Offset 0x0FF4 */
  uint32_t         VCSR_SET;               /* Offset 0x0FF8 */
  uint32_t         VCSR_BS;                /* Offset 0x0FFC */
} Universe_Memory;

volatile Universe_Memory *UNIVERSE;

/*
 * PCI_bus_write
 */
void PCI_bus_write(
  volatile uint32_t         * _addr,                  /* IN */
  uint32_t         _data                              /* IN */
)
{
  outport_32(_addr, _data);
}

uint32_t         PCI_bus_read(
  volatile uint32_t         *  _addr                  /* IN */
)
{
  uint32_t         data;

  inport_32(_addr, data);
  return data;
}

/********************************************************************
 ********************************************************************
 *********                                                  *********
 *********                                                  *********
 *********                                                  *********
 ********************************************************************
 ********************************************************************/

/*
 * Initializes the UNIVERSE chip.  This routine is called automatically
 * by the boot code.  This routine should be called by user code only if
 * a complete PPCn_60x VME initialization is required.
 */

void InitializeUniverse()
{
  uint32_t         pci_id;
  uint32_t         universe_temp_value;

  /*
   * Verify the UNIVERSE CHIP ID
   */
   (void)PCIConfigRead32(0,4,0,PCI_CONFIG_VENDOR_LOW, &pci_id);

   /*
    * compare to known ID
    */
   if (pci_id != 0x000010e3 ){
     DEBUG_puts ("Invalid PPCN_60X_UNIVERSE_CHIP_ID: ");
     rtems_fatal_error_occurred( 0x603e0bad );
   }

   (void)PCIConfigRead32(0,4,0,PCI_CONFIG_BAR_0, &universe_temp_value);
   UNIVERSE = (Universe_Memory *)(universe_temp_value & ~PCI_ADDRESS_IO_SPACE);

   /*
    * Set the UNIVERSE PCI Configuration Space Control and Status Register to
    * medium speed device, Target Back to Back Capable, Master Enable, Target
    * Memory Enable and Target IO Enable
    */
   PCIConfigWrite32(0,4,0,PCI_CONFIG_COMMAND, PCI_ENABLE_IO_SPACE |
   					      PCI_ENABLE_MEMORY_SPACE |
					      PCI_ENABLE_BUS_MASTER);

   /*
    * Turn off the sysfail by setting SYSFAIL bit to 1 on the VCSR_CLR register
    */
   PCI_bus_write( &UNIVERSE->VCSR_CLR, 0x40000000 );

#if 0
   /*
    * Set VMEbus Slave Image 0 Base Address to 0x04000000 on VSI0_BS register.
    */
   PCI_bus_write( &UNIVERSE->VSI0_BS, 0x04000000 );

   /*
    * Set VMEbus Slave Image 0 Bound Address to 0x05000000 on VSI0_BD register.
    */
   PCI_bus_write( &UNIVERSE->VSI0_BD, 0x05000000 );

   /*
    * VMEbus Slave Image 0 Translation Offset to 0x7C000000 on VSI0_TO
    * register. Map the VME base address 0x4000000 to local memory address 0x0
    */
   PCI_bus_write( &UNIVERSE->VSI0_TO, 0x7C000000 );

   /*
    * Set the VMEbus Slave Image 0 Control register with write posted,
    * read prefetch and AM code set for program, data, supervisor and user mode
    */
   PCI_bus_write( &UNIVERSE->VSI0_CTL, 0xE0F20000 );
#endif

   /*
    * Set the VMEbus Master Control register with retry forever, 256 bytes
    * posted write transfer count, VMEbus request level 3, RWD, PCI 32 bytes
    * aligned burst size and PCI bus number to be zero
    */
   PCI_bus_write( &UNIVERSE->MAST_CTL, 0x01C00000 );

   /*
    * VMEbus DMA Transfer Control register with 32 bit VMEbus Maximum Data
    * width, A32 VMEbus Address Space, AM code to be data, none-privilleged,
    * single and BLT cycles on VME bus and 64-bit PCI Bus Transactions enable
    PCI_bus_write( &UNIVERSE->DCTL, 0x00820180 );
    */

   PCI_bus_write( &UNIVERSE->LSI0_CTL, 0x80700040 );
   PCI_bus_write( &UNIVERSE->LSI0_BS,  0x04000000 );
   PCI_bus_write( &UNIVERSE->LSI0_BD,  0x05000000 );
   PCI_bus_write( &UNIVERSE->LSI0_TO,  0x7C000000 );


#if 0
   /*
    * Set the PCI Slave Image 0 Control register with posted write enable,
    * 32 bit data width, A32 VMEbus address base, AM code to be data,
    * none-privilleged, single and BLT cycles on VME bus with PCI
    * bus memory space.
   PCI_bus_write( &UNIVERSE->LSI0_CTL, 0xC0820100 );
    */
   PCI_bus_write( &UNIVERSE->LSI0_CTL, 0x80700040 );

   /*
    * Set the PCI Slave Image 0 Base Address to be
    * 0x0 on LSI0_BS register.
    */
   PCI_bus_write( &UNIVERSE->LSI0_BS, 0x00FF0000 );

   /*
    * Set the PCI Slave Image 0 Bound Address to be
    * 0xFFFFF000 on VSI0_BD register.
    */
   PCI_bus_write( &UNIVERSE->LSI0_BD, 0x00FFF000 );

   /*
    * Set the PCI Slave Image 0 Translation Offset to be
    * 0x0 on VSI0_TO register.
    * Note: If the actual VME address is bigger than 0x40000000, we need
    *   to set the PCI Slave Image 0 Translation Offset = 0x40000000
    *   register.
    *   i.e. if actual VME ADRR = 0x50000000, then we
    *     need to subtract it by 0x40000000 and set
    *      the LSI0_T0 register to be 0x40000000 and then
    *     perform a PCI data access by adding 0xC0000000 to
    *     0x10000000 -- which is came form the result of
    *     (0x50000000 - 0x40000000).
    */
   PCI_bus_write( &UNIVERSE->LSI0_TO, 0x0 );
#endif

   /*
    * Remove the Universe from VMEbus BI-Mode (bus-isolation).  Once out of
    * BI-Mode VMEbus accesses can be made.
    */

   universe_temp_value = PCI_bus_read( &UNIVERSE->MISC_CTL );

   if (universe_temp_value & 0x100000)
     PCI_bus_write( &UNIVERSE->MISC_CTL,(universe_temp_value | ~0xFF0FFFFF));
}

/*
 * Set the slave VME base address to the specified base address.
 * Note: Lower 12 bits[11:0] will be masked out prior to setting the VMEbus
 *       Slave Image 0 registers.
 */
void set_vme_base_address (
  uint32_t         base_address
)
{
  volatile uint32_t         temp;

  /*
   * Calculate the current size of the Slave VME image 0
   */
  temp = ( PCI_bus_read( &UNIVERSE->VSI0_BD) & 0xFFFFF000) -
          ( PCI_bus_read( &UNIVERSE->VSI0_BS) & 0xFFFFF000);

  /*
   * Set the VMEbus Slave Image 0 Base Address to be
   * the specifed base address on VSI0_BS register.
   */
   PCI_bus_write( &UNIVERSE->VSI0_BS, (base_address & 0xFFFFF000) );

  /*
   * Update the VMEbus Slave Image 0 Bound Address.
   */
  PCI_bus_write( &UNIVERSE->VSI0_BD, temp );

  /*
   * Update the VMEbus Slave Image 0 Translation Offset
   */
  temp = 0xFFFFFFFF - (base_address & 0xFFFFF000) + 1 + 0x80000000;
  PCI_bus_write( &UNIVERSE->VSI0_TO, temp );
}

/*
 * Gets the VME base address
 */
uint32_t         get_vme_base_address ()
{
  volatile uint32_t         temp;

  temp = PCI_bus_read( &UNIVERSE->VSI0_BS );
  temp &= 0xFFFFF000;
  return (temp);
}

uint32_t         get_vme_slave_size()
{
  volatile uint32_t         temp;
  temp  =  PCI_bus_read( &UNIVERSE->VSI0_BD);
  temp &= 0xFFFFF000;
  temp  = temp - get_vme_base_address ();
  return temp;
}

/*
 * Set the size of the VME slave image
 * Note: The maximum size is up to 24 M bytes. (00000000 - 017FFFFF)
 */
void set_vme_slave_size (uint32_t         size)
{
  volatile uint32_t         temp;

  if (size<0)
    size = 0;

  if (size > 0x17FFFFF)
    size = 0x17FFFFF;

  /*
   * Read the VME slave image base address
   */
  temp = get_vme_base_address ();

  /*
   * Update the VMEbus Slave Image 0 Bound Address.
   */
  temp = temp + (size & 0xFFFFF000);
  PCI_bus_write( &UNIVERSE->VSI0_BD, temp );
}

#if 0
/* XXXXX */
/*
 * Returns the 16 bit location specified by vme_ptr, which must be a
 * pointer to VME D16 space
 */
uint16_t         get_vme(
  uint16_t         *vme_ptr
)
{
  uint16_t         result;

  if (vme_ptr > (uint16_t*)0x3EFFFFFF)
  {
    /*
     * LSI0_TO register to 0x3EFFF000 if it had not been updated already
     */
    if (( PCI_bus_read( &UNIVERSE->LSI0_TO ) & 0xFFFFF000) != 0x3EFFF000)
         PCI_bus_write( &UNIVERSE->LSI0_TO, 0x3EFFF000 );

    result = (*(uint16_t*)(
               ((uint32_t)vme_ptr - 0x3EFFF000)+
                PPCN_60X_PCI_MEM_BASE) );
   }
   else
     result = (*(uint16_t*)
                ((uint32_t)vme_ptr+PPCN_60X_PCI_MEM_BASE));

   return result;
}

/*
 * Stores the 16 bit word at the location specified by vme_ptr, which must
 * be a pointer to VME D16 space
 */
void put_vme(
  uint16_t         *vme_ptr,
  uint16_t         value
)
{

  if (vme_ptr > (uint16_t*)0x3EFFFFFF) {
    /*
     * LSI0_TO register to 0x3EFFF000 if it had not been updated already
     */
     if (( PCI_bus_read( &UNIVERSE->LSI0_TO) & 0xFFFFF000) != 0x3EFFF000)
       PCI_bus_write( &UNIVERSE->LSI0_TO, 0x3EFFF000 );

    *(uint16_t*) (((uint32_t)vme_ptr - 0x3EFFF000) +
                            PPCN_60X_PCI_MEM_BASE) = value;
   }
   else
      *(uint16_t*)((uint32_t)vme_ptr +
                             PPCN_60X_PCI_MEM_BASE) = value;
}
#endif
