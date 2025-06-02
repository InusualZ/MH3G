.global __save_fpr
.global _savefpr_14
.global _savefpr_15
.global _savefpr_16
.global _savefpr_17
.global _savefpr_18
.global _savefpr_19
.global _savefpr_20
.global _savefpr_21
.global _savefpr_22
.global _savefpr_23
.global _savefpr_24
.global _savefpr_25
.global _savefpr_26
.global _savefpr_27
.global _savefpr_28
.global _savefpr_29
.global _savefpr_30
.global _savefpr_31

__save_fpr:
_savefpr_14: stfd %f14,-144(%r11)
_savefpr_15: stfd %f15,-136(%r11)
_savefpr_16: stfd %f16,-128(%r11)
_savefpr_17: stfd %f17,-120(%r11)
_savefpr_18: stfd %f18,-112(%r11)
_savefpr_19: stfd %f19,-104(%r11)
_savefpr_20: stfd %f20,-96(%r11)
_savefpr_21: stfd %f21,-88(%r11)
_savefpr_22: stfd %f22,-80(%r11)
_savefpr_23: stfd %f23,-72(%r11)
_savefpr_24: stfd %f24,-64(%r11)
_savefpr_25: stfd %f25,-56(%r11)
_savefpr_26: stfd %f26,-48(%r11)
_savefpr_27: stfd %f27,-40(%r11)
_savefpr_28: stfd %f28,-32(%r11)
_savefpr_29: stfd %f29,-24(%r11)
_savefpr_30: stfd %f30,-16(%r11)
_savefpr_31: stfd %f31,-8(%r11)
    blr

.global __restore_fpr
.global _restfpr_14
.global _restfpr_15
.global _restfpr_16
.global _restfpr_17
.global _restfpr_18
.global _restfpr_19
.global _restfpr_20
.global _restfpr_21
.global _restfpr_22
.global _restfpr_23
.global _restfpr_24
.global _restfpr_25
.global _restfpr_26
.global _restfpr_27
.global _restfpr_28
.global _restfpr_29
.global _restfpr_30
.global _restfpr_31

__restore_fpr:
_restfpr_14: lfd %f14,-144(%r11)
_restfpr_15: lfd %f15,-136(%r11)
_restfpr_16: lfd %f16,-128(%r11)
_restfpr_17: lfd %f17,-120(%r11)
_restfpr_18: lfd %f18,-112(%r11)
_restfpr_19: lfd %f19,-104(%r11)
_restfpr_20: lfd %f20,-96(%r11)
_restfpr_21: lfd %f21,-88(%r11)
_restfpr_22: lfd %f22,-80(%r11)
_restfpr_23: lfd %f23,-72(%r11)
_restfpr_24: lfd %f24,-64(%r11)
_restfpr_25: lfd %f25,-56(%r11)
_restfpr_26: lfd %f26,-48(%r11)
_restfpr_27: lfd %f27,-40(%r11)
_restfpr_28: lfd %f28,-32(%r11)
_restfpr_29: lfd %f29,-24(%r11)
_restfpr_30: lfd %f30,-16(%r11)
_restfpr_31: lfd %f31,-8(%r11)
    blr

.global __save_gpr
.global _savegpr_14
.global _savegpr_15
.global _savegpr_16
.global _savegpr_17
.global _savegpr_18
.global _savegpr_19
.global _savegpr_20
.global _savegpr_21
.global _savegpr_22
.global _savegpr_23
.global _savegpr_24
.global _savegpr_25
.global _savegpr_26
.global _savegpr_27
.global _savegpr_28
.global _savegpr_29
.global _savegpr_30
.global _savegpr_31

__save_gpr:
_savegpr_14: stw %r14,-72(%r11)
_savegpr_15: stw %r15,-68(%r11)
_savegpr_16: stw %r16,-64(%r11)
_savegpr_17: stw %r17,-60(%r11)
_savegpr_18: stw %r18,-56(%r11)
_savegpr_19: stw %r19,-52(%r11)
_savegpr_20: stw %r20,-48(%r11)
_savegpr_21: stw %r21,-44(%r11)
_savegpr_22: stw %r22,-40(%r11)
_savegpr_23: stw %r23,-36(%r11)
_savegpr_24: stw %r24,-32(%r11)
_savegpr_25: stw %r25,-28(%r11)
_savegpr_26: stw %r26,-24(%r11)
_savegpr_27: stw %r27,-20(%r11)
_savegpr_28: stw %r28,-16(%r11)
_savegpr_29: stw %r29,-12(%r11)
_savegpr_30: stw %r30,-8(%r11)
_savegpr_31: stw %r31,-4(%r11)
    blr

.global __restore_gpr
.global _restgpr_14
.global _restgpr_15
.global _restgpr_16
.global _restgpr_17
.global _restgpr_18
.global _restgpr_19
.global _restgpr_20
.global _restgpr_21
.global _restgpr_22
.global _restgpr_23
.global _restgpr_24
.global _restgpr_25
.global _restgpr_26
.global _restgpr_27
.global _restgpr_28
.global _restgpr_29
.global _restgpr_30
.global _restgpr_31

__restore_gpr:
_restgpr_14: lwz %r14,-72(%r11)
_restgpr_15: lwz %r15,-68(%r11)
_restgpr_16: lwz %r16,-64(%r11)
_restgpr_17: lwz %r17,-60(%r11)
_restgpr_18: lwz %r18,-56(%r11)
_restgpr_19: lwz %r19,-52(%r11)
_restgpr_20: lwz %r20,-48(%r11)
_restgpr_21: lwz %r21,-44(%r11)
_restgpr_22: lwz %r22,-40(%r11)
_restgpr_23: lwz %r23,-36(%r11)
_restgpr_24: lwz %r24,-32(%r11)
_restgpr_25: lwz %r25,-28(%r11)
_restgpr_26: lwz %r26,-24(%r11)
_restgpr_27: lwz %r27,-20(%r11)
_restgpr_28: lwz %r28,-16(%r11)
_restgpr_29: lwz %r29,-12(%r11)
_restgpr_30: lwz %r30,-8(%r11)
_restgpr_31: lwz %r31,-4(%r11)
    blr

.global _restgpr_14_x
.global _restgpr_15_x
.global _restgpr_16_x
.global _restgpr_17_x
.global _restgpr_18_x
.global _restgpr_19_x
.global _restgpr_20_x
.global _restgpr_21_x
.global _restgpr_22_x
.global _restgpr_23_x
.global _restgpr_24_x
.global _restgpr_25_x
.global _restgpr_26_x
.global _restgpr_27_x
.global _restgpr_28_x
.global _restgpr_29_x
.global _restgpr_30_x
.global _restgpr_31_x

_restgpr_14_x: lwz %r14,-0x48(%r11)
_restgpr_15_x: lwz %r15,-0x44(%r11)
_restgpr_16_x: lwz %r16,-0x40(%r11)
_restgpr_17_x: lwz %r17,-0x3C(%r11)
_restgpr_18_x: lwz %r18,-0x38(%r11)
_restgpr_19_x: lwz %r19,-0x34(%r11)
_restgpr_20_x: lwz %r20,-0x30(%r11)
_restgpr_21_x: lwz %r21,-0x2C(%r11)
_restgpr_22_x: lwz %r22,-0x28(%r11)
_restgpr_23_x: lwz %r23,-0x24(%r11)
_restgpr_24_x: lwz %r24,-0x20(%r11)
_restgpr_25_x: lwz %r25,-0x1C(%r11)
_restgpr_26_x: lwz %r26,-0x18(%r11)
_restgpr_27_x: lwz %r27,-0x14(%r11)
_restgpr_28_x: lwz %r28,-0x10(%r11)
_restgpr_29_x: lwz %r29,-0xC(%r11)
_restgpr_30_x: lwz %r30,-0x8(%r11)
_restgpr_31_x:
lwz %r0,0x4(%r11)
lwz %r31,-0x4(%r11)
mtlr %r0
mr %sp,%r11
blr

.global _restfpr_14_x
.global _restfpr_15_x
.global _restfpr_16_x
.global _restfpr_17_x
.global _restfpr_18_x
.global _restfpr_19_x
.global _restfpr_20_x
.global _restfpr_21_x
.global _restfpr_22_x
.global _restfpr_23_x
.global _restfpr_24_x
.global _restfpr_25_x
.global _restfpr_26_x
.global _restfpr_27_x
.global _restfpr_28_x
.global _restfpr_29_x
.global _restfpr_30_x
.global _restfpr_31_x

_restfpr_14_x: lfd %f14,-0x90(%r11)
_restfpr_15_x: lfd %f15,-0x88(%r11)
_restfpr_16_x: lfd %f16,-0x80(%r11)
_restfpr_17_x: lfd %f17,-0x78(%r11)
_restfpr_18_x: lfd %f18,-0x70(%r11)
_restfpr_19_x: lfd %f19,-0x68(%r11)
_restfpr_20_x: lfd %f20,-0x60(%r11)
_restfpr_21_x: lfd %f21,-0x58(%r11)
_restfpr_22_x: lfd %f22,-0x50(%r11)
_restfpr_23_x: lfd %f23,-0x48(%r11)
_restfpr_24_x: lfd %f24,-0x40(%r11)
_restfpr_25_x: lfd %f25,-0x38(%r11)
_restfpr_26_x: lfd %f26,-0x30(%r11)
_restfpr_27_x: lfd %f27,-0x28(%r11)
_restfpr_28_x: lfd %f28,-0x20(%r11)
_restfpr_29_x: lfd %f29,-0x18(%r11)
_restfpr_30_x: lfd %f30,-0x10(%r11)
_restfpr_31_x:
lwz %r0,0x4(%r11)
lfd %f31,-0x8(%r11)
mtlr %r0
mr %sp,%r11
blr