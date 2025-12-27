/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

/**
 * Compatibility header to support both BLE and ESB split transports.
 * 
 * When using ESB-only transport (CONFIG_ZMK_SPLIT_ESB=y with CONFIG_ZMK_SPLIT_BLE=n),
 * ZMK_SPLIT_BLE_PERIPHERAL_COUNT is not defined. This header provides a fallback
 * using the appropriate peripheral count config for the active transport.
 */

#ifndef ZMK_SPLIT_BLE_PERIPHERAL_COUNT

#if defined(CONFIG_ZMK_SPLIT_ESB_CENTRAL_PERIPHERALS)
/* ESB transport: use ESB peripheral count */
#define ZMK_SPLIT_BLE_PERIPHERAL_COUNT CONFIG_ZMK_SPLIT_ESB_CENTRAL_PERIPHERALS
#elif defined(CONFIG_ZMK_SPLIT_BLE_CENTRAL_PERIPHERALS)
/* BLE transport: use BLE peripheral count */
#define ZMK_SPLIT_BLE_PERIPHERAL_COUNT CONFIG_ZMK_SPLIT_BLE_CENTRAL_PERIPHERALS
#else
/* Default to 2 peripherals for typical split keyboards */
#define ZMK_SPLIT_BLE_PERIPHERAL_COUNT 2
#endif

#endif /* ZMK_SPLIT_BLE_PERIPHERAL_COUNT */
