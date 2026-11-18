/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"

#include "init_msm8226.h"

using android::base::GetProperty;

void vendor_load_properties()
{
    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("G800HQ") == 0) {
        /* kmini3g turkish version */
        property_override("ro.build.description", "kmini3gxx-user 4.4.2 KOT49H G800HXXU1ANL1 release-keys");
        set_ro_build_prop("fingerprint", "samsung/kmini3gxx/kmini3g:4.4.2/KOT49H/G800HXXU1ANL1:user/release-keys");
        set_ro_product_prop("device", "kmini3g");
        set_ro_product_prop("model", "SM-G800HQ");
        set_ro_product_prop("name", "kmini3gxx");
        gsm_properties("3", "0");
    } else if (bootloader.find("G800H") == 0) {
        /* kmini3g */
        property_override("ro.build.description", "kmini3gxx-user 6.0.1 MMB29M G800HXXU1CRJ1 release-keys");
        set_ro_build_prop("fingerprint", "samsung/kmini3gxx/kmini3g:6.0.1/MMB29M/G800HXXU1CRJ1:user/release-keys");
        set_ro_product_prop("device", "kmini3g");
        set_ro_product_prop("model", "SM-G800H");
        set_ro_product_prop("name", "kmini3gxx");
        gsm_properties("3", "0");
    } else {
        gsm_properties("3", "0");
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader << " setting build properties for "
        << device << " device" << std::endl;
}
