/**
 * @file bus_export.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-29
 * 
 * 
 */



 /* ==================== [Includes] ========================================== */
 #include "elab_i2c.h"
 #include "../Driver/driver_bus.h"
 #include "elab_export.h"
 /* ==================== [Defines] ========================================== */

static elab_i2c_bus_t soft_i2c_bus;
 /* ==================== [Macros] ============================================ */
 
 /* ==================== [Typedefs] ========================================== */
 
 /* ==================== [Static Prototypes] ========================================== */
void bus_export(void)
{
    
driver_i2c_bus_register(&soft_i2c_bus, "i2c0");

}
ELAB_INIT_EXPORT(bus_export, EXPORT_DRVIVER);

 /* ==================== [Static Variables] ========================================== */
 
 /* ==================== [Static Functions] ================================== */
 
 /* ==================== [Public Functions] ================================== */

