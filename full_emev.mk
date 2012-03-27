$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_small.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/generic.mk)

# Discard inherited values and use our own instead.
PRODUCT_NAME := full_renesas_emev
PRODUCT_DEVICE := emev
PRODUCT_MODEL := Full Renesas EMEV

include $(call all-makefiles-under,$(LOCAL_PATH))
