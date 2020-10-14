# gbemu
Yet another GameBoy emulator built in C++. Uses SFML. WIP, not functional yet.

This is a learning experiment regarding emulation, not something meant for serious uses.

Aiming for reasonable, but not perfect accuracy. Will try to document my decisions.

Also, I am not a professional C++ dev, haven't really used it since college. Wanted to give it a try again.

## Requirement
 - [SFML 2.5](https://www.sfml-dev.org/index.php)
 - CMake 3.14
 - C++17 compiler

## Building the project
In a terminal, navigate to the project folder.

### Application
- Run `cmake -Hstandalone -Bbuild/standalone`
- Run `cmake --build build/standalone/`

###  Unit Tests
- Run `cmake -Htest -Bbuild/test`
- Run `cmake --build build/test/`

## Usage
### Application
`./build/standalone/gbemu --path <pat to the rom>`

#### Options
- -h, --help: show help
- -p, --path: path to the rom you want to load

### Unit Tests
- `./build/test/gbemuTests`

## Test roms results
### Blargg's
| Test           | Result             | Note |
| -------------- | ------------------ | ---- |
| cgb_sound      | :x:                |      |
| cpu_instrs     | :warning:          | individual tests are successful, but not the all in one test. Issue with MBC1 implementation |
| dmg_sound      | :x:                |      |
| instr_timing   | :white_check_mark: |      |
| interrupt_time | :x:                |      |
| mem_timing     | :x:                |      |
| mem_timing-2   | :x:                |      |

### Mooneye's
#### Acceptance
| Test                    | Result             |
| ----------------------- | ------------------ |
| add_sp_e_timing         | :x:                |
| boot_div-S              | :x:                |
| boot_div-dmg0           | :x:                |
| boot_div-dmgABCmgb      | :x:                |
| boot_div2-S             | :x:                |
| boot_hwio-S             | :x:                |
| boot_hwio-dmg0          | :x:                |
| boot_hwio-dmgABCmgb     | :x:                |
| boot_regs-dmg0          | :x:                |
| boot_regs-dmgABC        | :x:                |
| boot_regs-mgb           | :x:                |
| boot_regs-sgb           | :x:                |
| boot_regs-sgb2          | :x:                |
| call_cc_timing          | :x:                |
| call_cc_timing2         | :x:                |
| call_timing             | :x:                |
| call_timing2            | :x:                |
| di_timing-GS            | :x:                |
| div_timing              | :x:                |
| ei_sequence             | :x:                |
| ei_timing               | :white_check_mark: |
| halt_ime0_ei            | :white_check_mark: |
| halt_ime0_nointr_timing | :x:                |
| halt_ime1_timing        | :white_check_mark: |
| halt_ime1_timing2-GS    | :x:                |
| if_ie_registers         | :white_check_mark: |
| intr_timing             | :x:                |
| jp_cc_timing            | :x:                |
| jp_timing               | :x:                |
| ld_hl_sp_e_timing       | :x:                |
| oam_dma_restart         | :x:                |
| oam_dma_start           | :x:                |
| oam_dma_timing          | :x:                |
| pop_timing              | :x:                |
| push_timing             | :x:                |
| rapid_di_ei             | :x:                |
| ret_cc_timing           | :x:                |
| ret_timing              | :x:                |
| reti_intr_timing        | :white_check_mark: |
| reti_timing             | :x:                |
| rst_timing              | :x:                |

##### bits
| Test       | Result             |
| ---------- | ------------------ |
| mem_oam    | :white_check_mark: |

##### instr
| Test           | Result             |
| -------------- | ------------------ |
| daa            | :white_check_mark: |
| reg_f          | :white_check_mark: |
| unused_hwio-GS | :x:                |

##### interrupts
| Test    | Result |
| ------- | ------ |
| ie_push | :x:    |

##### oam dma
| Test       | Result             | Note     |
| ---------- | ------------------ | -------- |
| basic      | :x:                |          |
| reg_read   | :white_check_mark: |          |
| sources-GS | :x:                | segfault |

##### ppu
| Test                        | Result |
| --------------------------- | ------ |
| hblank_ly_scx_timing-GS     | :x:    |
| intr_1_2_timing-GS          | :x:    |
| intr_2_0_timing             | :x:    |
| intr_2_mode0_timing         | :x:    |
| intr_2_mode0_timing_sprites | :x:    |
| intr_2_mode3_timing         | :x:    |
| intr_2_oam_ok_timing        | :x:    |
| lcdon_timing-GS             | :x:    |
| lcdon_write_timing-GS       | :x:    |
| stat_irq_blocking           | :x:    |
| stat_lyc_onoff              | :x:    |
| vblank_stat_intr-GS         | :x:    |

##### serial
Not implemented yet

##### timer
| Test                 | Result             |
| -------------------- | ------------------ |
| div_write            | :white_check_mark: |
| rapid_toggle         | :white_check_mark: |
| tim00                | :white_check_mark: |
| tim00_div_trigger    | :white_check_mark: |
| tim01                | :white_check_mark: |
| tim01_div_trigger    | :white_check_mark: |
| tim10                | :white_check_mark: |
| tim10_div_trigger    | :white_check_mark: |
| tim11                | :white_check_mark: |
| tim11_div_trigger    | :white_check_mark: |
| tima_reload          | :x:                |
| tima_write_reloading | :x:                |
| tma_write_reloading  | :x:                |

#### Emulator-only
##### MBC1
| Test       | Result             |
| ---------- | ------------------ |
| bits_bank1 | :white_check_mark: |
| bits_bank2 | :white_check_mark: |
| bits_mode  | :x:                |
| bits_ramg  | :white_check_mark: |
| ram_256kb  | :x:                |
| ram_64kb   | :x:                |
| rom_16Mb   | :x:                |
| rom_1Mb    | :x:                |
| rom_2Mb    | :x:                |
| rom_4Mb    | :x:                |
| rom_512kb  | :x:                |
| rom_8Mb    | :x:                |

##### MBC2
Not implemented yet

##### MBC5
Not implemented yet

#### Manual-only
Failed

#### Misc
Failed

## Technical References
- [Pan Docs](https://gbdev.io/pandocs/)
- [The Cycle-Accurate Game Boy Docs](https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf)
