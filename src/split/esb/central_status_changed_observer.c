/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/types.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/events/split_central_status_changed.h>
#include <zmk/split_peripheral_count.h>

/**
 * ESB Connection Status Observer
 * 
 * Unlike BLE, ESB doesn't have persistent connections. Peripherals are considered
 * "connected" as soon as the central starts receiving packets from them.
 * 
 * This observer raises initial "connected" events for all configured peripherals
 * shortly after boot, allowing the display widgets to show them as connected.
 */

static void esb_notify_connected_work_handler(struct k_work *work);
K_WORK_DELAYABLE_DEFINE(esb_notify_connected_work, esb_notify_connected_work_handler);

static void esb_notify_connected_work_handler(struct k_work *work) {
    LOG_DBG("ESB: Notifying all peripherals as connected");
    
    for (int i = 0; i < ZMK_SPLIT_BLE_PERIPHERAL_COUNT; i++) {
        raise_zmk_split_central_status_changed((struct zmk_split_central_status_changed){
            .slot = i,
            .connected = true,
        });
        k_msleep(100);
    }
}

static int zmk_split_esb_central_status_init(void) {
    /* Delay the connected notification to allow the display to initialize first */
    k_work_schedule(&esb_notify_connected_work, K_MSEC(1000));
    return 0;
}

SYS_INIT(zmk_split_esb_central_status_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
