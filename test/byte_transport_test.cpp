#include <byte_transport/Registry.h>
#include <byte_transport/RegistryUser.h>
#include <mock_transport/MockTransportDefinition.h>
#include <gtest/gtest.h>
#include <memory>

using Registry = pendarlab::lib::comm::byte_transport::Registry;
using RegistryUserAccess = pendarlab::lib::comm::byte_transport::RegistryUserAccess;
using MockTransportDefinition = pendarlab::lib::comm::byte_transport::MockTransportDefinition;

class ByteTransportTestSetup
{
public:
  ByteTransportTestSetup();

protected:
  Registry test_registry;
  std::unique_ptr<RegistryUserAccess> test_registry_user;
  MockTransportDefinition mock_transport_definition;
};

ByteTransportTestSetup::ByteTransportTestSetup() : test_registry_user(test_registry.createUser())
{
}

class ByteTransportInitialTest : public testing::Test, public ByteTransportTestSetup
{
protected:

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ByteTransportInitialTest, AddTransportDefinitionToEmptyRegistryShouldSucceed)
{
  bool result = test_registry.addTransportDefinition("transport-def-1", mock_transport_definition);
  EXPECT_EQ(result, true);
}

TEST_F(ByteTransportInitialTest, RemoveTransportDefinitionToEmptyRegistryShouldReturnFalse)
{
  bool result = test_registry.removeTransportDefinition("transport-def-1");
  EXPECT_EQ(result, false);
}

TEST_F(ByteTransportInitialTest, ShowRegisteredForEmptyRegistryShouldBeZero)
{
  EXPECT_EQ(test_registry.showRegistered().size(), 0);
}

TEST_F(ByteTransportInitialTest, ShowRegisteredForRegistryUserShouldBeZero)
{
  EXPECT_EQ(test_registry_user->showRegistered().size(), 0);
}

class ByteTransportRegistryHasEntriesTest : public testing::Test, public ByteTransportTestSetup
{
protected:
  void SetUp() override {
    test_registry.addTransportDefinition("registered-def", mock_transport_definition);
  }
  void TearDown() override {}
};

TEST_F(ByteTransportRegistryHasEntriesTest, AddTransportDefinitionWithSameNameShouldReturnFalse)
{
  bool result = test_registry.addTransportDefinition("registered-def", mock_transport_definition);
  EXPECT_EQ(result, false);
}

TEST_F(ByteTransportRegistryHasEntriesTest, RemoveRegisteredTransportDefinitionShouldReturnTrue)
{
  bool result = test_registry.removeTransportDefinition("registered-def");
  EXPECT_EQ(result, true);
}

TEST_F(ByteTransportRegistryHasEntriesTest, ShowRegisteredTransportDefinitionShouldShowProperly)
{
  EXPECT_EQ(test_registry.showRegistered().size(), 1);
  EXPECT_EQ(test_registry_user->showRegistered().size(), 1);
}

TEST_F(ByteTransportRegistryHasEntriesTest, IsRegisteredShouldReturnTrueForRegisteredDef)
{
  EXPECT_EQ(test_registry.isRegistered("registered-def"), true);
  EXPECT_EQ(test_registry_user->isRegistered("registered-def"), true);
}

TEST_F(ByteTransportRegistryHasEntriesTest, IsRegisteredShouldReturnFalseForNonRegisteredDef)
{
  EXPECT_EQ(test_registry.isRegistered("not-registered-def"), false);
  EXPECT_EQ(test_registry_user->isRegistered("not-registered-def"), false);
}

TEST_F(ByteTransportRegistryHasEntriesTest, OperatorAtIsNotNullptrForRegisteredDef)
{
  EXPECT_NE(test_registry["registered-def"], nullptr);
  EXPECT_NE((*test_registry_user)["registered-def"], nullptr);
}

TEST_F(ByteTransportRegistryHasEntriesTest, OperatorAtIsNullptrForUnregisteredDef)
{
  EXPECT_EQ(test_registry["not-registered-def"], nullptr);
  EXPECT_EQ((*test_registry_user)["not-registered-def"], nullptr);
}


class ByteTransportRegistryHasRemovedEntryTest : public testing::Test, public ByteTransportTestSetup
{
protected:
  void SetUp() override {
    test_registry.addTransportDefinition("registered-def", mock_transport_definition);
    test_registry.addTransportDefinition("removed-def", mock_transport_definition);
    test_registry.removeTransportDefinition("removed-def");
  }
  void TearDown() override {}
};

TEST_F(ByteTransportRegistryHasRemovedEntryTest, IsRegisteredShouldReturnFalseForNonRegisteredDef)
{
  EXPECT_EQ(test_registry.isRegistered("removed-def"), false);
  EXPECT_EQ(test_registry_user->isRegistered("removed-def"), false);
}

TEST_F(ByteTransportRegistryHasRemovedEntryTest, ShowRegisteredTransportDefinitionShouldShowProperly)
{
  ASSERT_EQ(test_registry.showRegistered().size(), 1);
  ASSERT_EQ(test_registry_user->showRegistered().size(), 1);
  EXPECT_EQ(test_registry.showRegistered()[0], "registered-def");
  EXPECT_EQ(test_registry_user->showRegistered()[0], "registered-def");
}

TEST_F(ByteTransportRegistryHasRemovedEntryTest, OperatorAtIsNotNullptrForRegisteredDef)
{
  EXPECT_NE(test_registry["registered-def"], nullptr);
  EXPECT_NE((*test_registry_user)["registered-def"], nullptr);
}

TEST_F(ByteTransportRegistryHasRemovedEntryTest, OperatorAtIsNullptrForRemovedDef)
{
  EXPECT_EQ(test_registry["removed-def"], nullptr);
  EXPECT_EQ((*test_registry_user)["removed-def"], nullptr);
}

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  int test_result = RUN_ALL_TESTS();
  return test_result;
}