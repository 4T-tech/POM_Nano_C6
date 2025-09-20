idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES driver i2c_eeprom i2c_init lis2mdl_reg)