#include "system.h"
#include "oled.h"

static struct oled_operations m_oled_opr;

static struct system_operations sys_opr;



void SystemInit()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    
    register_system_operations( &sys_opr );
    sys_opr.iomux( P32P33_I2C );
    
    register_oled_operations( &m_oled_opr );
    m_oled_opr.init();
}

void main()
{
    SystemInit();
    
    m_oled_opr.putascii( 5, 5, 'A' );
    m_oled_opr.flush();
    
    while( 1 );
}