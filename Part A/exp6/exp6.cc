#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE("DynamicGlobalRoutingExample");
int main(int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);
  Config::SetDefault("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue(true));
  /* Configuration. */

  /* Build nodes. */
  NodeContainer term_0;
  term_0.Create(1);
  NodeContainer term_1;
  term_1.Create(1);
  NodeContainer term_2;
  term_2.Create(1);
  NodeContainer term_3;
  term_3.Create(1);
  NodeContainer term_4;
  term_4.Create(1);
  NodeContainer term_5;
  term_5.Create(1);
  NodeContainer term_6;
  term_6.Create(1);

  /* Build link. */
  CsmaHelper csma_hub_0;
  csma_hub_0.SetChannelAttribute("DataRate", DataRateValue(5000000));
  csma_hub_0.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
  PointToPointHelper p2p_p2p_0;
  p2p_p2p_0.SetDeviceAttribute("DataRate", DataRateValue(5000000));
  p2p_p2p_0.SetChannelAttribute("Delay", TimeValue(MilliSeconds(10)));
  /*PointToPointHelper p2p_p2p_1;
  p2p_p2p_1.SetDeviceAttribute ("DataRate", DataRateValue (100000000));
  p2p_p2p_1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10000)));
  PointToPointHelper p2p_p2p_2;
  p2p_p2p_2.SetDeviceAttribute ("DataRate", DataRateValue (100000000));
  p2p_p2p_2.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10000)));
  PointToPointHelper p2p_p2p_3;
  p2p_p2p_3.SetDeviceAttribute ("DataRate", DataRateValue (100000000));
  p2p_p2p_3.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10000)));*/

  /* Build link net device container. */
  NodeContainer all_hub_0;
  all_hub_0.Add(term_2);
  all_hub_0.Add(term_3);
  all_hub_0.Add(term_4);
  all_hub_0.Add(term_5);
  NetDeviceContainer ndc_hub_0 = csma_hub_0.Install(all_hub_0);
  NodeContainer all_p2p_0;
  all_p2p_0.Add(term_0);
  all_p2p_0.Add(term_2);
  NetDeviceContainer ndc_p2p_0 = p2p_p2p_0.Install(all_p2p_0);
  NodeContainer all_p2p_1;
  all_p2p_1.Add(term_1);
  all_p2p_1.Add(term_2);
  NetDeviceContainer ndc_p2p_1 = p2p_p2p_0.Install(all_p2p_1);
  NodeContainer all_p2p_2;
  all_p2p_2.Add(term_1);
  all_p2p_2.Add(term_6);
  NetDeviceContainer ndc_p2p_2 = p2p_p2p_0.Install(all_p2p_2);
  NodeContainer all_p2p_3;
  all_p2p_3.Add(term_5);
  all_p2p_3.Add(term_6);
  NetDeviceContainer ndc_p2p_3 = p2p_p2p_0.Install(all_p2p_3);

  /* Install the IP stack. */
  InternetStackHelper internetStackH;
  internetStackH.Install(term_0);
  internetStackH.Install(term_1);
  internetStackH.Install(term_2);
  internetStackH.Install(term_3);
  internetStackH.Install(term_4);
  internetStackH.Install(term_5);
  internetStackH.Install(term_6);

  /* IP assign. */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.250.1.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_hub_0 = ipv4.Assign(ndc_hub_0);
  ipv4.SetBase("10.0.1.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_0 = ipv4.Assign(ndc_p2p_0);
  ipv4.SetBase("10.0.2.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_1 = ipv4.Assign(ndc_p2p_1);
  ipv4.SetBase("10.0.3.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_2 = ipv4.Assign(ndc_p2p_2);
  ipv4.SetBase("172.16.1.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_3 = ipv4.Assign(ndc_p2p_3);

  /* Generate Route. */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  /* Generate Application. */
  // NS_LOG_INFO ("Create Applications.");
  uint16_t port = 9; // Discard port (RFC 863)
  OnOffHelper onoff("ns3::UdpSocketFactory",
                    InetSocketAddress(iface_ndc_p2p_3.GetAddress(1), port));
  onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  onoff.SetAttribute("DataRate", StringValue("2kbps"));
  onoff.SetAttribute("PacketSize", UintegerValue(50));
  ApplicationContainer apps = onoff.Install(term_1.Get(0));
  apps.Start(Seconds(1.0));
  apps.Stop(Seconds(10.0));
  OnOffHelper onoff2("ns3::UdpSocketFactory", InetSocketAddress(iface_ndc_p2p_2.GetAddress(1), port));
  onoff2.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff2.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  onoff2.SetAttribute("DataRate", StringValue("2kbps"));
  onoff2.SetAttribute("PacketSize", UintegerValue(50));
  ApplicationContainer apps2 = onoff2.Install(term_1.Get(0));
  apps2.Start(Seconds(11.0));
  apps2.Stop(Seconds(16.0));
  PacketSinkHelper sink("ns3::UdpSocketFactory", Address(InetSocketAddress(Ipv4Address::GetAny(), port)));
  apps = sink.Install(term_6.Get(0));
  apps.Start(Seconds(1.0));
  apps.Stop(Seconds(10.0));
  PacketSinkHelper sink2("ns3::UdpSocketFactory",
                         Address(InetSocketAddress(Ipv4Address::GetAny(), port)));
  apps2 = sink2.Install(term_6.Get(0));
  apps2.Start(Seconds(11.0));
  apps2.Stop(Seconds(16.0));
  AsciiTraceHelper ascii;
  Ptr<OutputStreamWrapper> stream = ascii.CreateFileStream("dynamic-global routing.tr");
  p2p_p2p_0.EnableAsciiAll(stream);
  csma_hub_0.EnableAsciiAll(stream);
  internetStackH.EnableAsciiIpv4All(stream);
  p2p_p2p_0.EnablePcapAll("dynamic-global-routing");
  csma_hub_0.EnablePcapAll("dynamic-global-routing", false);
  Ptr<Node> n1 = term_1.Get(0);
  Ptr<Ipv4> ipv41 = n1->GetObject<Ipv4>();
  uint32_t ipv4ifIndex1 = 2;
  Simulator::Schedule(Seconds(2), &Ipv4::SetDown, ipv41, ipv4ifIndex1);
  Simulator::Schedule(Seconds(4), &Ipv4::SetUp, ipv41, ipv4ifIndex1);
  Ptr<Node> n6 = term_6.Get(0);
  Ptr<Ipv4> ipv46 = n6->GetObject<Ipv4>();
  uint32_t ipv4ifIndex6 = 2;
  Simulator::Schedule(Seconds(6), &Ipv4::SetDown, ipv46, ipv4ifIndex6);
  Simulator::Schedule(Seconds(8), &Ipv4::SetUp, ipv46, ipv4ifIndex6);
  Simulator::Schedule(Seconds(12), &Ipv4::SetDown, ipv41, ipv4ifIndex1);
  Simulator::Schedule(Seconds(14), &Ipv4::SetUp, ipv41, ipv4ifIndex1);
  Ipv4GlobalRoutingHelper g;
  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper>("dynamic-global-routing.routes", std::ios::out);
  g.PrintRoutingTableAllAt(Seconds(12), routingStream);
  AnimationInterface anim("exp1.xml");
  Ptr<Node> n = term_0.Get(0);
  anim.SetConstantPosition(term_0.Get(0), 0.0, 75.0);
  anim.SetConstantPosition(term_1.Get(0), 25.0, 50.0);
  anim.SetConstantPosition(term_2.Get(0), 0.0, 25.0);
  anim.SetConstantPosition(term_3.Get(0), 80.0, 50.0);
  anim.SetConstantPosition(term_4.Get(0), 50.0, 50.0);
  anim.SetConstantPosition(term_5.Get(0), 75.5, 25.0);
  anim.SetConstantPosition(term_6.Get(0), 100.0, 25.0);
  NS_LOG_INFO("Run Simulation.");
  Simulator::Run();
  Simulator::Destroy();
  NS_LOG_INFO("Done.");
}
