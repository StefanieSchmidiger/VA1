/**
 * \file
 * \brief Configuration header file for SDK_BitIO
 *
 * This header file is used to configure settings of the SDK Bit I/O module.
 */
#ifndef __DQ1_CONFIG_H
#define __DQ1_CONFIG_H

#ifndef DQ1_CONFIG_PORT_NAME
  #define DQ1_CONFIG_PORT_NAME       PORTB
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef DQ1_CONFIG_GPIO_NAME
  #define DQ1_CONFIG_GPIO_NAME       GPIOB
    /*!< name of GPIO, is pointer to GPIO_Type */
#endif

#ifndef DQ1_CONFIG_PIN_NUMBER
  #define DQ1_CONFIG_PIN_NUMBER      0u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef DQ1_CONFIG_INIT_PIN_VALUE
  #define DQ1_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define DQ1_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define DQ1_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define DQ1_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef DQ1_CONFIG_INIT_PIN_DIRECTION
  #define DQ1_CONFIG_INIT_PIN_DIRECTION  DQ1_CONFIG_INIT_PIN_DIRECTION_INPUT
#endif

#ifndef DQ1_CONFIG_DO_PIN_MUXING
  #define DQ1_CONFIG_DO_PIN_MUXING  1
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#endif /* __DQ1_CONFIG_H */
