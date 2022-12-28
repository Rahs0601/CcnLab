#include "ns3/core-module.h"
#include "ns3/global-route-manager.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/bridge-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
// new
#include "ns3/netanim-module.h"

using namespace ns3;
// new
NS_LOG_COMPONENT_DEFINE("Firstscript");

int main(int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);

  /* Configuration. */
  // new
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  std::string animFile = "exp1.xml";

  /* Build nodes. */
  NodeContainer term_0;
  term_0.Create(1);
  NodeContainer term_1;
  term_1.Create(1);
  NodeContainer term_2;
  term_2.Create(1);
  NodeContainer term_3;
  term_3.Create(1);

  /* Build link. */
  // change -> 100000000 to 5000000 , 10000 -> 2
  PointToPointHelper p2p_p2p_0;
  p2p_p2p_0.SetDeviceAttribute("DataRate", DataRateValue(5000000));
  p2p_p2p_0.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
  PointToPointHelper p2p_p2p_1;
  p2p_p2p_1.SetDeviceAttribute("DataRate", DataRateValue(5000000));
  p2p_p2p_1.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
  PointToPointHelper p2p_p2p_2;
  p2p_p2p_2.SetDeviceAttribute("DataRate", DataRateValue(5000000));
  p2p_p2p_2.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));

  /* Build link net device container. */
  NodeContainer all_p2p_0;
  all_p2p_0.Add(term_0);
  all_p2p_0.Add(term_1);
  NetDeviceContainer ndc_p2p_0 = p2p_p2p_0.Install(all_p2p_0);
  NodeContainer all_p2p_1;
  all_p2p_1.Add(term_1);
  all_p2p_1.Add(term_2);
  NetDeviceContainer ndc_p2p_1 = p2p_p2p_1.Install(all_p2p_1);
  NodeContainer all_p2p_2;
  all_p2p_2.Add(term_2);
  all_p2p_2.Add(term_3);
  NetDeviceContainer ndc_p2p_2 = p2p_p2p_2.Install(all_p2p_2);

  /* Install the IP stack. */
  InternetStackHelper internetStackH;
  internetStackH.Install(term_0);
  internetStackH.Install(term_1);
  internetStackH.Install(term_2);
  internetStackH.Install(term_3);

  /* IP assign. */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_0 = ipv4.Assign(ndc_p2p_0);
  ipv4.SetBase("10.0.1.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_1 = ipv4.Assign(ndc_p2p_1);
  ipv4.SetBase("10.0.2.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_2 = ipv4.Assign(ndc_p2p_2);

  /* Generate Route. */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  /* Generate Application. */
  //  client_udpEcho_0.SetAttribute ("MaxPackets", UintegerValue (1->20));
  uint16_t port_udpEcho_0 = 111;
  UdpEchoServerHelper server_udpEcho_0(port_udpEcho_0);
  ApplicationContainer apps_udpEcho_0 = server_udpEcho_0.Install(term_1.Get(0));
  apps_udpEcho_0.Start(Seconds(0.0));
  apps_udpEcho_0.Stop(Seconds(10.0));
  Time interPacketInterval_udpEcho_0 = Seconds(1.0);
  UdpEchoClientHelper client_udpEcho_0(iface_ndc_p2p_0.GetAddress(1), 111);
  client_udpEcho_0.SetAttribute("MaxPackets", UintegerValue(20));
  client_udpEcho_0.SetAttribute("Interval", TimeValue(interPacketInterval_udpEcho_0));
  client_udpEcho_0.SetAttribute("PacketSize", UintegerValue(1024));
  apps_udpEcho_0 = client_udpEcho_0.Install(term_0.Get(0));
  apps_udpEcho_0.Start(Seconds(0.1));
  apps_udpEcho_0.Stop(Seconds(10.0));
  uint16_t port_udpEcho_1 = 112;
  UdpEchoServerHelper server_udpEcho_1(port_udpEcho_1);
  ApplicationContainer apps_udpEcho_1 = server_udpEcho_1.Install(term_2.Get(0));
  apps_udpEcho_1.Start(Seconds(1.0));
  apps_udpEcho_1.Stop(Seconds(10.0));
  Time interPacketInterval_udpEcho_1 = Seconds(1.0);
  UdpEchoClientHelper client_udpEcho_1(iface_ndc_p2p_1.GetAddress(1), 112);
  client_udpEcho_1.SetAttribute("MaxPackets", UintegerValue(20));
  client_udpEcho_1.SetAttribute("Interval", TimeValue(interPacketInterval_udpEcho_1));
  client_udpEcho_1.SetAttribute("PacketSize", UintegerValue(1024));
  apps_udpEcho_1 = client_udpEcho_1.Install(term_1.Get(0));
  apps_udpEcho_1.Start(Seconds(1.1));
  apps_udpEcho_1.Stop(Seconds(10.0));
  uint16_t port_udpEcho_2 = 113;
  UdpEchoServerHelper server_udpEcho_2(port_udpEcho_2);
  ApplicationContainer apps_udpEcho_2 = server_udpEcho_2.Install(term_3.Get(0));
  apps_udpEcho_2.Start(Seconds(3.0));
  apps_udpEcho_2.Stop(Seconds(10.0));
  Time interPacketInterval_udpEcho_2 = Seconds(1.0);
  UdpEchoClientHelper client_udpEcho_2(iface_ndc_p2p_2.GetAddress(1), 113);
  client_udpEcho_2.SetAttribute("MaxPackets", UintegerValue(20));
  client_udpEcho_2.SetAttribute("Interval", TimeValue(interPacketInterval_udpEcho_2));
  client_udpEcho_2.SetAttribute("PacketSize", UintegerValue(1024));
  apps_udpEcho_2 = client_udpEcho_2.Install(term_2.Get(0));
  apps_udpEcho_2.Start(Seconds(3.1));
  apps_udpEcho_2.Stop(Seconds(10.0));

  /* Simulation. */
  // new
  AnimationInterface anim(animFile);
  Ptr<Node> n = term_0.Get(0);
  anim.SetConstantPosition(n, 200, 200);
  n = term_1.Get(0);
  anim.SetConstantPosition(n, 300, 200);
  n = term_2.Get(0);
  anim.SetConstantPosition(n, 250, 100);
  n = term_3.Get(0);
  anim.SetConstantPosition(n, 350, 100);

  /* Pcap output. */
  /* Stop the simulation after x seconds. */
  uint32_t stopTime = 11;
  Simulator::Stop(Seconds(stopTime));
  /* Start and clean simulation. */
  Simulator::Run();
  Simulator::Destroy();
}
