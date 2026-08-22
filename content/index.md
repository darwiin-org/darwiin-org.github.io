---
name: Home
---

# PureDarwin

<div class="terminal-section">
    <img src="/icns/hexley.png" class="img-fluid layered-img" alt="Hexley Screenshot">

<div class="card terminal-card">
<pre>console 800 x 600 @ 0xfd000000
[ PCI configuration end, bridges 1, devices 6 ]
ClockRTC::getGMTTimeOfDay Reading rtc date with linux method : 1519974600
mcache: 1 CPU(s), 64 bytes CPU cache line size
mbinit: done [64 MB total pool size, (42/21) split]
rooting via boot-uuid from /chosen: 4FC1C8BC-610C-3C97-A28D-9F2390B766BA
Waiting on &lt;dict ID="0"&gt;&lt;key&gt;IOProviderClass&lt;/key&gt;&lt;string id="1"&gt;IOResources&lt;/string&gt;&lt;string id="2"&gt;IOResource
Match&lt;/string&gt;&lt;string ID="2"&gt;boot-uuid-media&lt;/string&gt;&lt;/dict&gt;
Got boot device = IOService:/AppleI386PlatformExpert/pci/AppleI386PCI/pci8086,7010@1,1/AppleIntelPII
XATARoot/CHN0@0/AppleIntelPIIXATA/ATADeviceNub@0/IOATABlockStorageDriver/IOATABlockStorageDevice/IO
BlockStorageDriver/QEMU HARDDISK Media/IOFDiskPartitionBSD root: disk0s1, major 1, minor 1
jnl: b(1, 1): journal start/end pointers reset! (s 0x3b6400 e 0x5de000)
hfs: mounted PureDarwin-10.13.3 on device b(1, 1)
VM Swap Subsystem is ON
Failed to open swap file 30
Failed to open swap file 30
vm_swap_create_file failed @ 32 secs
load_init_program: attempting to load /sbin/launchd
** /dev/rdisk0s1
** Root file system
   Executing fsck_hfs (version hfs-).
** Checking Journaled HFS Plus volume.
   The volume name is PureDarwin-10.13.3
** Checking extents overflow file.
** Checking catalog file.
** Checking multi-linked files.
** Checking catalog hierarchy.
** Checking extended attributes file.
** Checking volume bitmap.
** Checking volume information.
** The volume PureDarwin-10.13.3 appears to be OK.
hfs: Removed 0 orphaned / unlinked files and 12 directories
/sbin/launchd: line 91: sync: command not found
bash-3.2#
bash-3.2#
bash-3.2#
bash-3.2#</pre>
    </div>
</div>


Darwin is the open source operating system from Apple that forms the base for macOS. PureDarwin is a community project that fills in the gaps to make Darwin usable.

The project's main focus is providing useful documentation and making it easier for developers and open-source enthusiasts to engage with Darwin.


# Test Build

The PD-17.4 Test Build is a minimal system, unlike previous versions like PureDarwin Xmas with a graphical interface. It’s distributed as a virtual machine disk (VMDK) and runs via software like QEMU.

Due to the lack of proprietary macOS components, the community must develop alternatives, leaving elements like network drivers and hardware support incomplete. This build is intended for developers and open-source enthusiasts to explore Darwin development outside of macOS.

<small><i>Based on Darwin 17, which corresponds to macOS High Sierra (10.13.x).</i></small>

<a href="/download.html" class="btn btn-primary">Download PureDarwin (17.4 Test)</a>
